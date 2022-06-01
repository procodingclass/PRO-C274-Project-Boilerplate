#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <RTClib.h>
#include "lcd_custom_character.h"

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4);

File file;

String names[20];
String dates[20];
String current_date = "";

void setup() {
  Serial.begin(9600);
  SD.begin();
  rtc.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();

  file = SD.open("birthday.txt", FILE_READ);

  happy_birthday_text();
  animate();

  lcd.clear();

  read_current_date();
  read_file();

  match_date();

}

void happy_birthday_text() {
  /* write code to print "Happy Birthday" on the welcome screen */
}

void display_char(int x, int y, int id) {
  lcd.setCursor(x, y);
  lcd.write(id);
}

void animate() {

  /*write code to display a birthday cake animation on the welcome screen.
    You can use the customized characters’ arrays given in the lcd_custom_character.h file.
    You can also add your own customized characters*/



}

void read_file() {
  String paragraph;
  int i = 0;

  if (file) {
    while (file.available()) {
      String data = file.readStringUntil(':');
      names[i] = data;
      String data1 = file.readStringUntil('\n');
      dates[i] = data1;
      i++;
    }
  }
}

void read_current_date() {

  DateTime now = rtc.now();
  current_date = "";

  if (now.day() < 10) {
    current_date.concat("0");
  }
  current_date.concat(now.day());
  current_date.concat("-");
  if (now.month() < 10) {
    current_date.concat("0");
  }
  current_date.concat(now.month());

}

void match_date() {

    /*change the code in a way that the birthday message 
    is displayed on the LCD display instead of the serial monitor*/

  int found = 0;
  for (int i = 0; i < 20; i++) {
    int flag = 0;
    for (int j = 0; j < 5; j++) {
      if (current_date[j] == dates[i][j]) {
        flag++;
      }
    }
    if (flag == 5) {
      Serial.print("Happy Birthday, ");
      Serial.println(names[i]);
      delay(3000);
      found = 1;
    }
  }

  if (found == 0) {
    Serial.println("No birthday");
    Serial.println("today!!");
    delay(5000);
  }

}

void loop() {

}
// Kipas menyala otomatis saat kondisi suhu Panas

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2      // Pin tempelkan sensor DHT11 di pin 2
#define DHTTYPE DHT11 // Jenis sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

int relayPin = 8;   // Pin tempelkan relay di pin 7

// Konfigurasi LCD SDA=A4 SCL =A5
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C 0x27, 16 kolom, 2 baris

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(relayPin, OUTPUT);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Suhu:");
}
// Variabel global untuk menyimpan suhu sebelumnya
float previousTemperature = 0.0;
void loop() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Gagal membaca data dari sensor DHT!");
    return;
  }

  Serial.print("Suhu: ");
  Serial.println(temperature);

if (temperature != previousTemperature) {
    lcd.setCursor(0, 1);
    lcd.print("                "); // Membersihkan tampilan sebelumnya
    lcd.setCursor(0, 1);
     lcd.print("Suhu : ");
    lcd.print(temperature);
    previousTemperature = temperature;
  }

  if (temperature > 35.00) {
    digitalWrite(relayPin, LOW); // Mengaktifkan relay
    Serial.println("Relay ON");
    lcd.setCursor(0, 0);
    lcd.print("Relay: ON ");
  } else {
    digitalWrite(relayPin, HIGH);  // Mematikan relay
    Serial.println("Relay OFF");
    lcd.setCursor(0, 0);
    lcd.print("Relay: OFF");
  }

  delay(2000); // Menggunakan delay agar pembacaan suhu tidak terlalu cepat
}

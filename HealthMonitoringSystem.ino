#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const float thi = 37.5; // Upper threshold for temperature in Celsius
const float tlo = 36.0; // Lower threshold for temperature

const int hbhi = 100; // Upper threshold for heartbeat
const int hblo = 60;  // Lower threshold for heartbeat

const int bphi = 120; // Upper threshold for blood pressure
const int bplo = 90;  // Lower threshold for blood pressure

void setup()
{
    pinMode(A0, INPUT); // Temperature sensor
    pinMode(A1, INPUT); // Heartbeat (simulated by potentiometer)
    pinMode(A2, INPUT); // Blood pressure sensor

    pinMode(7, OUTPUT);  // LED for temperature status
    pinMode(8, OUTPUT);  // LED for heartbeat status
    pinMode(13, OUTPUT); // LED for blood pressure status

    Serial.begin(9600);
    lcd.begin(16, 2);

    // Display header on LCD
    lcd.print("Temp | HB | BP");
}

void loop()
{
    // Reading sensor values
    int SensorVal = analogRead(A0); // Temperature sensor reading
    int hbeatRaw = analogRead(A1);  // Heartbeat sensor (simulated by potentiometer)
    int bpRaw = analogRead(A2);     // Blood pressure sensor

    // Converting temperature sensor value to Celsius
    float voltage = (SensorVal / 1023.0) * 5.0;
    float temperatureC = (voltage - 0.5) * 100;

    // Scale heartbeat (simulated) to realistic values (60 - 100 BPM)
    int heartbeat = map(hbeatRaw, 0, 1023, 60, 100);

    // Scale blood pressure to realistic values (90 - 120 mmHg)
    int bp = map(bpRaw, 0, 1023, 90, 120);

    delay(500); // Delay for stable readings

    // Clear second row for new readings
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear row

    // Limit the temperature display to the nearest integer for better fitting
    lcd.setCursor(0, 1);          // Start at the first column, second row
    lcd.print((int)temperatureC); // Print rounded temperature as integer
    lcd.print("C");               // Append "C"

    // Add status for temperature with a space
    if (temperatureC <= tlo)
    {
        lcd.print("(L)"); // Low temperature
    }
    else if (temperatureC >= thi)
    {
        lcd.print("(H)"); // High temperature
    }
    else
    {
        lcd.print("(N)"); // Normal temperature
    }

    // Add a space before Heartbeat
    lcd.setCursor(7, 1);  // Start at the 7th column for Heartbeat
    lcd.print(heartbeat); // Print heartbeat value
    if (heartbeat < hblo)
    {
        lcd.print("(L)"); // Low heartbeat
    }
    else if (heartbeat > hbhi)
    {
        lcd.print("(H)"); // High heartbeat
    }
    else
    {
        lcd.print("(N)"); // Normal heartbeat
    }

    // Add a space before Blood Pressure
    lcd.setCursor(13, 1); // Start at the 13th column for Blood Pressure
    lcd.print(bp);        // Print blood pressure value (no unit needed)

    // Print values to Serial Monitor for debugging
    Serial.print("Temp: ");
    Serial.print(temperatureC);
    Serial.print(" C ");
    Serial.print("Heartbeat: ");
    Serial.print(heartbeat);
    Serial.print(" BPM ");
    Serial.print("BP: ");
    Serial.println(bp);

    delay(1000); // 1-second delay between updates
}

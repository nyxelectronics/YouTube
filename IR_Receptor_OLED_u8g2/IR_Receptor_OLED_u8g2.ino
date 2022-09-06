#include <Arduino.h>
#include <U8x8lib.h>

#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

String sAddress, sCommand, sRaw;

void setup()
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_open_iconic_embedded_4x4);
  u8x8.drawGlyph(6, 3, 0x50);
  u8x8.setFont(u8x8_font_8x13B_1x2_f);
  u8x8.drawString(3, 0, "RECEPTOR IR");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop()
{
  if (IrReceiver.decode())
  {
    u8x8.clear();
    sAddress = String(IrReceiver.decodedIRData.address, HEX);
    sCommand = String(IrReceiver.decodedIRData.command, HEX);
    sRaw = String(IrReceiver.decodedIRData.decodedRawData, HEX);
    sAddress.toUpperCase();
    sCommand.toUpperCase();
    sRaw.toUpperCase();
    u8x8.setCursor(0, 2);
    u8x8.print("Address: 0x");
    u8x8.setCursor(11, 2);
    u8x8.print(sAddress);
    u8x8.setCursor(0, 4);
    u8x8.print("Command: 0x");
    u8x8.setCursor(11, 4);
    u8x8.print(sCommand);
    u8x8.setCursor(0, 6);
    u8x8.print("Raw: 0x");
    u8x8.setCursor(7, 6);
    u8x8.print(sRaw);
    switch (IrReceiver.decodedIRData.protocol)
    {
      case NEC:
        u8x8.drawString(6, 0, "NEC");
        break;
      case SAMSUNG:
        u8x8.drawString(5, 0, "SAMSUNG");
        break;
      case SONY:
        u8x8.drawString(6, 0, "SONY");
        break;
      case LG:
        u8x8.drawString(7, 0, "LG");
        break;
      case PANASONIC:
        u8x8.drawString(3, 0, "PANASONIC");
        break;
      case JVC:
        u8x8.drawString(6, 0, "JVC");
        break;
      case RC5:
        u8x8.drawString(6, 0, "RC5");
        break;
      case RC6:
        u8x8.drawString(6, 0, "RC6");
        break;
      case DISH:
        u8x8.drawString(6, 0, "DISH");
        break;
      case SHARP:
        u8x8.drawString(5, 0, "SHARP");
        break;
      case WHYNTER:
        u8x8.drawString(5, 0, "WHYNTER");
        break;
      case DENON:
        u8x8.drawString(5, 0, "DENON");
        break;
      default:
      case UNKNOWN:
        u8x8.drawString(4, 0, "UNKNOWN");
        break;
    }
    IrReceiver.resume();
  }
}

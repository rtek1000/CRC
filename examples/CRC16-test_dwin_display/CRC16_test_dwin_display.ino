//
//    FILE: CRC16_test_dwin_display.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2023-07-25
//    (c) : MIT
//
//  MODIFICATION: Rtek1000
// PURPOSE: get Dwin CRC for displays
//    DATE: 2024-03-04
//    (c) : MIT


#include "CRC16.h"

CRC16 crc(CRC16_MODBUS_POLYNOME,
          CRC16_MODBUS_INITIAL,
          CRC16_MODBUS_XOR_OUT,
          CRC16_MODBUS_REV_IN,
          CRC16_MODBUS_REV_OUT);

#define SWAP_BYTES(u16Value) ((u16Value << 8) | (u16Value >> 8));

void setup() {
  Serial.begin(115200);
  Serial.println(__FILE__);

  // Dwin display order: 5A A5 06 '83 20 00 01' E9 AA
  // 5A A5: header
  // 06: length
  // 83: Read VP command
  // 20 00: VP addr
  // 01: data
  // E9 AA: CRC16 checksum (for 83-20-00-01 only)

  //5a a5 0a 82 10 00 12 34 56 78 90 ac 3c

  //5a a5 14 80 08 22 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 a6 2a

  //5a a5 41 82 12 34 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 90 bf 87

  uint8_t order_arr0[] = { 0x5A, 0xA5, 0x06, 0x83, 0x20, 0x00, 0x01, 0x00, 0x00 };

  uint8_t order_arr1[] = { 0x5a, 0xa5, 0x0a, 0x82, 0x10, 0x00, 0x12, 0x34,
                           0x56, 0x78, 0x90, 0x00, 0x00 };

  uint8_t order_arr2[] = { 0x5a, 0xa5, 0x14, 0x80, 0x08, 0x22, 0x12, 0x34,
                           0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90,
                           0x12, 0x34, 0x56, 0x78, 0x90, 0x00, 0x00 };

  uint8_t order_arr3[] = { 0x5a, 0xa5, 0x41, 0x82, 0x12, 0x34, 0x12, 0x34,
                           0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90,
                           0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56,
                           0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12,
                           0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78,
                           0x90, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34,
                           0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90,
                           0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56,
                           0x78, 0x90, 0x00, 0x00 };

  uint8_t order_arr4[] = { 0x5A, 0xA5, 0x06, 0x83, 0x20, 0x00, 0x01, 0xE9, 0xAA };

  uint8_t order_arr5[] = { 0x5a, 0xa5, 0x0a, 0x82, 0x10, 0x00, 0x12, 0x34,
                           0x56, 0x78, 0x90, 0xac, 0x3c };

  uint8_t order_arr6[] = { 0x5a, 0xa5, 0x14, 0x80, 0x08, 0x22, 0x12, 0x34,
                           0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90,
                           0x12, 0x34, 0x56, 0x78, 0x90, 0xa6, 0x2a };

  uint8_t order_arr7[] = { 0x5a, 0xa5, 0x41, 0x82, 0x12, 0x34, 0x12, 0x34,
                           0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90,
                           0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56,
                           0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12,
                           0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78,
                           0x90, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34,
                           0x56, 0x78, 0x90, 0x12, 0x34, 0x56, 0x78, 0x90,
                           0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34, 0x56,
                           0x78, 0x90, 0xbf, 0x87 };

  Serial.println(F("\nOrder 3:"));
  print_DWIN_Order(order_arr3);

  calc_DWIN_CRC(order_arr3, false);

  print_DWIN_Order(order_arr3);

  Serial.print(F("\nOnly check the Order 2: "));

  Serial.println(F("\nOrder 2:"));
  print_DWIN_Order(order_arr2);

  if (calc_DWIN_CRC(order_arr2, true)) {
    Serial.println(F("CRC OK"));
  } else {
    Serial.println(F("CRC ERROR"));
  }

  Serial.print(F("\nOnly check the Order 7: "));

  Serial.println(F("\nOrder 7:"));
  print_DWIN_Order(order_arr7);

  if (calc_DWIN_CRC(order_arr7, true)) {
    Serial.println(F("CRC OK"));
  } else {
    Serial.println(F("CRC ERROR"));
  }
}

void loop() {
}

bool calc_DWIN_CRC(uint8_t *array, bool only_check) {
  crc.restart();

  for (int i = 3; i < (array[2] + 1); i++) {
    crc.add(array[i]);
  }

  uint16_t res = crc.calc();
  uint8_t res0 = res;
  uint8_t res1 = res >> 8;

  if ((array[array[2] + 1] == res0) && (array[array[2] + 2] == res1)) {
    return true;
  }

  if (only_check == false) {
    array[array[2] + 1] = res0;
    array[array[2] + 2] = res1;
  }

  return false;
}

void print_DWIN_Order(const uint8_t *array) {
  for (int i = 0; i <= (array[2] + 2); i++) {
    if (array[i] <= 9) Serial.print(F("0"));
    Serial.print(array[i], HEX);
    Serial.print(" ");
  }

  Serial.println();
}

// -- END OF FILE --

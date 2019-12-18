#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS31_FUNCTIONREG ; 
 int /*<<< orphan*/  IS31_REG_SHUTDOWN ; 
 int /*<<< orphan*/  IS31_REG_SHUTDOWN_OFF ; 
 int /*<<< orphan*/  IS31_REG_SHUTDOWN_ON ; 
 int /*<<< orphan*/  chThdSleepMilliseconds (int) ; 
 int /*<<< orphan*/  is31_read_register (int,int,int*) ; 
 int /*<<< orphan*/  is31_write_data (int,int*,int) ; 
 int /*<<< orphan*/  is31_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void set_led_bit (uint8_t page, uint8_t *led_control_word, uint8_t led_addr, uint8_t action) {
  //returns 2 bytes: led control register address and byte to write
  //action: 0 - off, 1 - on, 2 - toggle, 4 - blink on, 5 - blink off, 6 - toggle blink

  uint8_t control_reg_addr, column_bit, column_byte, temp, blink_bit;

  //check for valid led address
  if (led_addr < 0 || led_addr > 87 || led_addr % 10 > 8) {
    return;
  }

  blink_bit = action>>2;//check for blink bit
  action &= ~(1<<2); //strip blink bit

  //led_addr tens column is pin#, ones column is bit position in 8-bit mask
  control_reg_addr = ((led_addr / 10) % 10 - 1 ) * 0x02;// A-matrix is every other byte
  control_reg_addr += blink_bit == 1 ? 0x12 : 0x00;//if blink_bit, shift 12 bytes to blink register

  is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_ON);
  chThdSleepMilliseconds(5);
  is31_read_register(page, control_reg_addr, &temp);//maintain status of leds on this byte
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_OFF);

  column_bit = 1<<(led_addr % 10 - 1);
  column_byte = temp;

  switch(action) {
    case 0:
      column_byte &= ~column_bit;
      break;
    case 1:
      column_byte |= column_bit;
      break;
    case 2:
      column_byte ^= column_bit;
      break;
  }

  //return word to be written in register
  led_control_word[0] = control_reg_addr;
  led_control_word[1] = column_byte;
  is31_write_data (page, led_control_word, 0x02);
}
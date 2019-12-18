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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS31_FUNCTIONREG ; 
 int /*<<< orphan*/  IS31_REG_SHUTDOWN ; 
 int /*<<< orphan*/  IS31_REG_SHUTDOWN_OFF ; 
 int /*<<< orphan*/  IS31_REG_SHUTDOWN_ON ; 
 int /*<<< orphan*/  chThdSleepMilliseconds (int) ; 
 int /*<<< orphan*/  is31_read_register (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  is31_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_led_bit (scalar_t__,scalar_t__*,scalar_t__,scalar_t__) ; 

void set_lock_leds(uint8_t led_addr, uint8_t led_action, uint8_t page) {
  uint8_t temp;
  uint8_t led_control_word[2] = {0};

  //blink if all leds are on
  if (page == 0) {
    is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_ON);
    chThdSleepMilliseconds(5);
    is31_read_register(0, 0x00, &temp);
    is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_OFF);

    if (temp == 0xFF) {
      led_action |= (1<<2); //set blink bit
    }
  }

  set_led_bit(page,led_control_word,led_addr,led_action);
}
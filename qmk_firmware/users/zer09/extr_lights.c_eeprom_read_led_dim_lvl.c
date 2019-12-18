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

/* Variables and functions */
 int /*<<< orphan*/  EECONFIG_LED_DIM_LVL ; 
 int eeprom_read_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_write_byte (int /*<<< orphan*/ ,int) ; 
 int led_dim ; 

void eeprom_read_led_dim_lvl(void) {
  led_dim = eeprom_read_byte(EECONFIG_LED_DIM_LVL);

  if (led_dim > 8 || led_dim < 0) {
    led_dim = 0;
    eeprom_write_byte(EECONFIG_LED_DIM_LVL, led_dim);
  }
}
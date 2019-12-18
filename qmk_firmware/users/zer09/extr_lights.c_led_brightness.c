#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  EECONFIG_LED_DIM_LVL ; 
#define  RGDWN 129 
#define  RGUP 128 
 int /*<<< orphan*/  eeprom_write_byte (int /*<<< orphan*/ ,int) ; 
 int led_dim ; 

bool led_brightness(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case RGUP:
    if (record->event.pressed && led_dim > 0) {
      led_dim--;
      eeprom_write_byte(EECONFIG_LED_DIM_LVL, led_dim);
    }

    return true;
    break;
  case RGDWN:
    if (record->event.pressed && led_dim < 8) {
      led_dim++;
      eeprom_write_byte(EECONFIG_LED_DIM_LVL, led_dim);
    }

    return true;
    break;
  default:
    return false;
    break;
  }
}
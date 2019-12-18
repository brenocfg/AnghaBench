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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int USB_LED_CAPS_LOCK ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  the50_led_off () ; 
 int /*<<< orphan*/  the50_led_on () ; 

void led_set_user(uint8_t usb_led) {
  // Turn LED On/Off for Caps Lock
  if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
    the50_led_on();
  } else {
    the50_led_off();
  }
}
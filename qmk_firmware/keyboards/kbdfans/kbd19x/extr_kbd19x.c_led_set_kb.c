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
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  kbd19x_caps_led_off () ; 
 int /*<<< orphan*/  kbd19x_caps_led_on () ; 
 int /*<<< orphan*/  kbd19x_nmlk_led_off () ; 
 int /*<<< orphan*/  kbd19x_nmlk_led_on () ; 
 int /*<<< orphan*/  kbd19x_sclk_led_off () ; 
 int /*<<< orphan*/  kbd19x_sclk_led_on () ; 
 int /*<<< orphan*/  led_set_user (int) ; 

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    kbd19x_nmlk_led_on();
  } else {
    kbd19x_nmlk_led_off();
  }

  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    kbd19x_caps_led_on();
  } else {
    kbd19x_caps_led_off();
  }

  if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    kbd19x_sclk_led_on();
  } else {
    kbd19x_sclk_led_off();
  }

  led_set_user(usb_led);
}
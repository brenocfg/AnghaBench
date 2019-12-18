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
 int /*<<< orphan*/  led_set_user (int) ; 
 int /*<<< orphan*/  xd60_caps_led_off () ; 
 int /*<<< orphan*/  xd60_caps_led_on () ; 

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		xd60_caps_led_on();
	} else {
		xd60_caps_led_off();
  }

  // if (usb_led & (1<<USB_LED_NUM_LOCK)) {
	// xd60_esc_led_on();
	// } else {
	// xd60_esc_led_off();
  // }

  // if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
	// xd60_fn_led_on();
	// } else {
	// xd60_fn_led_off();
  // }

	led_set_user(usb_led);
}
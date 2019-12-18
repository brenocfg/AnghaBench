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
 int USB_LED_NUM_LOCK ; 
 int /*<<< orphan*/  rgblight_sethsv_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    // Illuminate the LED under the Num Lock key
    rgblight_sethsv_at(0, 0, 127, 1);
  } else {
    rgblight_sethsv_at(0, 0, 0, 1);
  }
}
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
 int /*<<< orphan*/  rgblight_disable () ; 
 int /*<<< orphan*/  rgblight_enable () ; 

void led_set_user(uint8_t usb_led) {
  #ifdef RGBLIGHT_ENABLE
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    rgblight_enable();
  } else {
    rgblight_disable();
  }
  #endif //RGBLIGHT_ENABLE
}
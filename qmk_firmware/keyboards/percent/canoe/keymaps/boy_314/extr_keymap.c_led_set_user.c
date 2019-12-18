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
 int /*<<< orphan*/  HSV_RED ; 
 int /*<<< orphan*/  HSV_TURQUOISE ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ) ; 

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        rgblight_sethsv(HSV_RED);
    } else {
        rgblight_sethsv(HSV_TURQUOISE);
    }
}
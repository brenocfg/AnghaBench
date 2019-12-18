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
 int /*<<< orphan*/  FLED_CAPS_H ; 
 int /*<<< orphan*/  FLED_CAPS_S ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  fled_val ; 
 int /*<<< orphan*/ * fleds ; 
 int /*<<< orphan*/  led_set_user (int) ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setrgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void led_set_kb(uint8_t usb_led) {
    // Set indicator LED appropriately, whether it is used or not
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        sethsv(FLED_CAPS_H, FLED_CAPS_S, fled_val, &fleds[0]);
    } else {
        setrgb(0, 0, 0, &fleds[0]);
    }

    rgblight_set();
	led_set_user(usb_led);
}
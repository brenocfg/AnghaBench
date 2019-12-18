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
 int /*<<< orphan*/  rgblight_disable_noeeprom () ; 
 int /*<<< orphan*/  rgblight_enable_noeeprom () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void led_set_user(uint8_t usb_led) {
    // Turn LEDs On/Off for Caps Lock
    if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(0, 0, 80);
    } else {
        rgblight_sethsv_noeeprom(0, 0, 80);
        rgblight_disable_noeeprom();
    }
}
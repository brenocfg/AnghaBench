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
 int /*<<< orphan*/  HSV_CAPS ; 
 int /*<<< orphan*/  HSV_DEFAULT ; 
 scalar_t__ IS_HOST_LED_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ) ; 

void set_lights_default(void) {
    #ifdef RGBLIGHT_ENABLE
        if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
            rgblight_sethsv_noeeprom(HSV_CAPS);
        } else {
            rgblight_sethsv_noeeprom(HSV_DEFAULT);
        }
    #endif
}
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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 scalar_t__ KC_WAKE ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_STATIC_LIGHT ; 
 int _initialized ; 
 int _leds_dirty ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_eeprom_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!_initialized) {
        // Static lighting is amenable to customization.
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        _initialized = true;
    };
    if (keycode == KC_WAKE) {
        // Turn the lights off before going to sleep.
        rgblight_sethsv_eeprom_helper(0, 0, 0, false);
    } else {
        _leds_dirty = true;
    };
    return true;
}
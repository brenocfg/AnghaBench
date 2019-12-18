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
typedef  int uint16_t ;

/* Variables and functions */
 int MOD_MASK_ALT ; 
 int MOD_MASK_CTRL ; 
 int MOD_MASK_SHIFT ; 
 int /*<<< orphan*/  _COLEMAK ; 
 int /*<<< orphan*/  _NUMERIC ; 
 int _leds_dirty ; 
 int get_mods () ; 
 scalar_t__ layer_state_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_eeprom_helper (int,int,int,int) ; 

void modal_leds(void) {
    uint8_t mods = get_mods();
    uint16_t hue = 355;  // Rough match to printed case.
    uint8_t saturation = 255;
    uint8_t value = 0;
    if (layer_state_is(_COLEMAK)) { hue -= 50; saturation -= 20; value += 20; };
    if (layer_state_is(_NUMERIC)) { value += 30; };
    if (mods & MOD_MASK_SHIFT) { saturation -= 20; value += 30; };
    if (mods & MOD_MASK_ALT) { hue -= 100; saturation -= 20; value += 30; };
    if (mods & MOD_MASK_CTRL) { hue -= 200; saturation -= 20; value += 30; };
    // rgblight_sethsv_eeprom_helper is not a great API function but it does
    // affect both halves of a split keyboard.
    rgblight_sethsv_eeprom_helper(hue, saturation, value, false);
    _leds_dirty = false;
}
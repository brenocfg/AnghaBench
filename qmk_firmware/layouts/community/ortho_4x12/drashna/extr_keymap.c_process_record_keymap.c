#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int led_level; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
#define  BACKLIT 129 
 int /*<<< orphan*/  KC_RSFT ; 
#define  TH_LVL 128 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  eeconfig_update_kb (int /*<<< orphan*/ ) ; 
 TYPE_4__ keyboard_config ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  layer_state_set_kb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  planck_ez_left_led_level (int) ; 
 int /*<<< orphan*/  planck_ez_right_led_level (int) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef BACKLIGHT_ENABLE
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#    ifdef BACKLIGHT_ENABLE
                backlight_step();
#    endif
            } else {
                unregister_code(KC_RSFT);
            }
            break;
#endif
#ifdef KEYBOARD_planck_ez
        case TH_LVL:
            if (record->event.pressed) {
                 keyboard_config.led_level++;
                 if (keyboard_config.led_level > 4) {
                    keyboard_config.led_level = 0;
                 }
                 planck_ez_right_led_level((uint8_t)keyboard_config.led_level * 255 / 4 );
                 planck_ez_left_led_level((uint8_t)keyboard_config.led_level * 255 / 4 );
                 eeconfig_update_kb(keyboard_config.raw);
                 layer_state_set_kb(layer_state);
            }
            break;
#endif
    }
    return true;
}
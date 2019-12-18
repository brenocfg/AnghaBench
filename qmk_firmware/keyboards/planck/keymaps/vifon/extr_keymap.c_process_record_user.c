#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  key; scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
typedef  unsigned long int32_t ;

/* Variables and functions */
 int DYN_REC_STOP ; 
 scalar_t__ IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_LSFT ; 
 scalar_t__ KC_TRNS ; 
#define  KM_HOLD 136 
#define  KM_LW 135 
#define  KM_NUM 134 
#define  KM_PP_GAME 133 
#define  KM_PP_HOLD 132 
#define  KM_RS 131 
#define  KM_RST 130 
#define  KM_SHLK 129 
#define  KM_SLP 128 
 int MO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _DL ; 
 int /*<<< orphan*/  _DYN ; 
 int /*<<< orphan*/  _LW ; 
 int /*<<< orphan*/  _NM ; 
 unsigned long _PP ; 
 unsigned long _QW ; 
 int /*<<< orphan*/  _RS ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  backlight_toggle () ; 
 int /*<<< orphan*/  bootloader_jump () ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  default_layer_set (unsigned long) ; 
 unsigned long default_layer_state ; 
 int /*<<< orphan*/  enable_gaming_layer () ; 
 scalar_t__ keymap_key_to_keycode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 unsigned long layer_state ; 
 int /*<<< orphan*/  process_record (TYPE_2__*) ; 
 int /*<<< orphan*/  process_record_dynamic_macro (int,TYPE_2__*) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int timer_elapsed (int) ; 
 int timer_read () ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t key_timer;
    static uint8_t ignore_up_events = 0;

    uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);
    if (!process_record_dynamic_macro(macro_kc, record)) {
        return false;
    }

    if (ignore_up_events > 0 && keycode != MO(_DYN) && keycode != KM_HOLD && !record->event.pressed) {
        ignore_up_events -= 1;
        return false;
    }

    switch (keycode) {
    case KM_LW:
        if (record->event.pressed) {
            layer_on(_LW);
        } else {
            layer_off(_LW);
        }
        update_tri_layer(_LW, _RS, _DL);
        return false;
        break;
    case KM_RS:
        if (record->event.pressed) {
            layer_on(_RS);
        } else {
            layer_off(_RS);
        }
        update_tri_layer(_LW, _RS, _DL);
        return false;
        break;
    case KM_SHLK:
        register_code(KC_LSFT);
        break;
    case KM_HOLD:
        if (!record->event.pressed) {
            ignore_up_events += 1;
        }
        break;
    case KM_RST:
    {
        /* Make slash available on the PP layer. */
        if ((1UL << _PP) & default_layer_state) {
            int32_t old_default_layer_state = default_layer_state;
            int32_t old_layer_state = layer_state;

            layer_state = 0;
            default_layer_state = (1UL << _QW);

            process_record(record);

            layer_state = old_layer_state;
            default_layer_state = old_default_layer_state;

            return false;
        }
    }

        if (record->event.pressed) {
            key_timer = timer_read();
        } else {
            if (timer_elapsed(key_timer) >= 500) {
                clear_keyboard();
                backlight_toggle();
                _delay_ms(250);
                backlight_toggle();
                bootloader_jump();
            }
        }
        break;
    case KM_PP_GAME:
        if (!record->event.pressed) {
            enable_gaming_layer();
        }
        break;
    case KM_PP_HOLD:
        if (record->event.pressed) {
            key_timer = timer_read();
        } else {
            if (timer_elapsed(key_timer) >= 250) {
                enable_gaming_layer();
            } else {
                default_layer_set(1UL << _PP);
            }
        }
        break;
    case KM_NUM:
        layer_on(_NM);
        break;
    case KM_SLP:
        if (record->event.pressed) {
            _delay_ms(250);
        }
        break;
    }


    if (record->event.pressed
        && IS_LAYER_ON(_NM)
        && keymap_key_to_keycode(_NM, record->event.key) == KC_TRNS) {

        layer_off(_NM);
    }

    return true;
}
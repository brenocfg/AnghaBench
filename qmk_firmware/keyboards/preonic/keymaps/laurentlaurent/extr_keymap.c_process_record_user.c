#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  BACKLIT 135 
#define  DYN_REC_START1 134 
#define  DYN_REC_START2 133 
#define  DYN_REC_STOP 132 
 int /*<<< orphan*/  KC_BSPC ; 
 int /*<<< orphan*/  KC_RSFT ; 
#define  LOWER 131 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 int PORTE ; 
#define  QWERTY 130 
#define  QWWIN 129 
#define  RAISE 128 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _QWERTY_MAC ; 
 int /*<<< orphan*/  _QWERTY_WIN ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  key_timer ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_record_dynamic_macro (int,TYPE_2__*) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  timer_thresh ; 
 int /*<<< orphan*/  tone_macro1_record ; 
 int /*<<< orphan*/  tone_macro2_record ; 
 int /*<<< orphan*/  tone_macro_record_stop ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool            process_record_user(uint16_t keycode, keyrecord_t *record) {
    // For dynamic macros
    if (!process_record_dynamic_macro(keycode, record)) {
// Play sound on Macro stop
#ifdef AUDIO_ENABLE
        switch (keycode) {
            case DYN_REC_STOP:
                if (record->event.pressed) {
                    PLAY_SONG(tone_macro_record_stop);
                }
                return false;
                break;
        }
#endif
        return false;
    }

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY_MAC);
            }
            return false;
            break;
        case QWWIN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY_WIN);
            }
            return false;
            break;
        // Reinstate these cases if COLEMAK, DVORAK are included in the layouts
        /*case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
          */
        case LOWER:
            if (record->event.pressed) {
                key_timer = timer_read(); // For Backspace on tap
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                // Backspace on tap
                if (timer_elapsed(key_timer) < timer_thresh) {
                    tap_code(KC_BSPC);
                }
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                key_timer = timer_read(); // For Backspace on tap
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                // Backspace on tap
                if (timer_elapsed(key_timer) < timer_thresh) {
                    tap_code(KC_BSPC);
                }
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
#ifdef __AVR__
                PORTE &= ~(1 << 6);
#endif
            } else {
                unregister_code(KC_RSFT);
#ifdef __AVR__
                PORTE |= (1 << 6);
#endif
            }
            return false;
            break;
#ifdef AUDIO_ENABLE
            // Play sound on Macro record start
        case DYN_REC_START1:
            if (record->event.pressed) {
                PLAY_SONG(tone_macro1_record);
            }
            return false;
            break;
        case DYN_REC_START2:
            if (record->event.pressed) {
                PLAY_SONG(tone_macro2_record);
            }
            return false;
            break;
#endif
    }
    return true;
}
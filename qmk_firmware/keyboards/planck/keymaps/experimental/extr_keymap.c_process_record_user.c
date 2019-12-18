#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  BACKLIT 143 
#define  COLEMAK 142 
#define  DVORAK 141 
#define  EXT_PLV 140 
 int /*<<< orphan*/  KC_RSFT ; 
#define  LOWER 139 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  PLOVER 138 
#define  QWERTY 137 
#define  RAISE 136 
#define  RGBLED_DECREASE_HUE 135 
#define  RGBLED_DECREASE_SAT 134 
#define  RGBLED_DECREASE_VAL 133 
#define  RGBLED_INCREASE_HUE 132 
#define  RGBLED_INCREASE_SAT 131 
#define  RGBLED_INCREASE_VAL 130 
#define  RGBLED_STEP_MODE 129 
#define  RGBLED_TOGGLE 128 
 int /*<<< orphan*/  _ADJUST ; 
 unsigned long _COLEMAK ; 
 unsigned long _DVORAK ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _PLOVER ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  breathing_period_set (int) ; 
 int /*<<< orphan*/  breathing_pulse () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_decrease_hue () ; 
 int /*<<< orphan*/  rgblight_decrease_sat () ; 
 int /*<<< orphan*/  rgblight_decrease_val () ; 
 int /*<<< orphan*/  rgblight_increase_hue () ; 
 int /*<<< orphan*/  rgblight_increase_sat () ; 
 int /*<<< orphan*/  rgblight_increase_val () ; 
 int /*<<< orphan*/  rgblight_step () ; 
 int /*<<< orphan*/  rgblight_toggle () ; 
 int /*<<< orphan*/  stop_all_notes () ; 
 int /*<<< orphan*/  tone_colemak ; 
 int /*<<< orphan*/  tone_dvorak ; 
 int /*<<< orphan*/  tone_plover ; 
 int /*<<< orphan*/  tone_plover_gb ; 
 int /*<<< orphan*/  tone_qwerty ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_qwerty);
            #endif
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          break;
      return false;
        case COLEMAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            persistent_default_layer_set(1UL<<_COLEMAK);
          }
          break;
      return false;
        case DVORAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dvorak);
            #endif
            persistent_default_layer_set(1UL<<_DVORAK);
          }
          break;
      return false;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            #ifdef BACKLIGHT_ENABLE
                breathing_period_set(2);
                breathing_pulse();
            #endif
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          break;
      return false;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            #ifdef BACKLIGHT_ENABLE
                breathing_period_set(2);
                breathing_pulse();
            #endif
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          break;
      return false;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      return false;
        case PLOVER:
          if (!record->event.pressed) {
            #ifdef AUDIO_ENABLE
              stop_all_notes();
              PLAY_SONG(tone_plover);
            #endif
            layer_on(_PLOVER);
          }
        break;
      return false;
        case EXT_PLV:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_plover_gb);
            #endif
            layer_off(_PLOVER);
          }
        break;
      return false;

    case RGBLED_TOGGLE:
      //led operations
      if (record->event.pressed) {
        rgblight_toggle();
      }
      return false;
      break;
    case RGBLED_INCREASE_HUE:
      if (record->event.pressed) {
        rgblight_increase_hue();
      }
      return false;
      break;
    case RGBLED_DECREASE_HUE:
      if (record->event.pressed) {
        rgblight_decrease_hue();
      }
      return false;
      break;
    case RGBLED_INCREASE_SAT:
      if (record->event.pressed) {
        rgblight_increase_sat();
      }
      return false;
      break;
    case RGBLED_DECREASE_SAT:
      if (record->event.pressed) {
        rgblight_decrease_sat();
      }
      return false;
      break;
    case RGBLED_INCREASE_VAL:
      if (record->event.pressed) {
        rgblight_increase_val();
      }
      return false;
      break;
    case RGBLED_DECREASE_VAL:
      if (record->event.pressed) {
        rgblight_decrease_val();
      }
      return false;
      break;
    case RGBLED_STEP_MODE:
      if (record->event.pressed) {
        rgblight_step();
      }
      return false;
      break;


      }
  return true;
}
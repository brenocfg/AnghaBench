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
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int nkro; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
#define  DEAD 135 
#define  EXT_PLV 134 
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_O ; 
 int /*<<< orphan*/  KC_P ; 
 int /*<<< orphan*/  KC_R ; 
 int /*<<< orphan*/  KC_T ; 
 int /*<<< orphan*/  KC_W ; 
#define  LOWER 133 
 int /*<<< orphan*/  ONESHOT_PRESSED ; 
 int /*<<< orphan*/  ONESHOT_START ; 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  PLOVER 132 
#define  QWERTY 131 
#define  RAISE 130 
#define  TOG_PLV 129 
#define  WORKMAN 128 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _DEAD ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _PLOVER ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 unsigned long _WORKMAN ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  clear_oneshot_layer_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_keymap () ; 
 int /*<<< orphan*/  eeconfig_update_keymap (int /*<<< orphan*/ ) ; 
 TYPE_4__ keymap_config ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_oneshot_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_all_notes () ; 
 int /*<<< orphan*/  tone_plover ; 
 int /*<<< orphan*/  tone_plover_gb ; 
 int /*<<< orphan*/  tone_qwerty ; 
 int /*<<< orphan*/  tone_workman ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_workman);
        #endif
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case DEAD:
      if (record->event.pressed) {
        layer_on(_DEAD);
        set_oneshot_layer(_DEAD, ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(tone_plover);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  case TOG_PLV:
    if (record->event.pressed) {
      register_code(KC_R);
      register_code(KC_W);
      register_code(KC_T);
      register_code(KC_C);
      register_code(KC_P);
      register_code(KC_O);
      clear_keyboard();
    }
    return false;
    break;
  }
  return true;
}
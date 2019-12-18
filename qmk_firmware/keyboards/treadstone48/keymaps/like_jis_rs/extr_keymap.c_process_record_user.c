#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_8__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_10__ {int swap_lalt_lgui; } ;
struct TYPE_9__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  BASE 135 
#define  BASES 134 
#define  KANJI 133 
 int /*<<< orphan*/  KC_LANG2 ; 
#define  LOWER 132 
#define  LOWRS 131 
 int /*<<< orphan*/  L_BASE ; 
 int /*<<< orphan*/  L_BASES ; 
#define  RAISE 130 
#define  RGBRST 129 
#define  RGB_MOD 128 
 int /*<<< orphan*/  RGB_current_mode ; 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_LALT (char*) ; 
 int /*<<< orphan*/  UPDATE_KEYMAP_STATUS () ; 
 int /*<<< orphan*/  UPDATE_KEY_STATUS (int,TYPE_2__*) ; 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _LOWRS ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  default_layer_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeconfig_update_rgblight_default () ; 
 TYPE_5__ keymap_config ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 TYPE_3__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_step () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_change_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  UPDATE_KEY_STATUS(keycode, record);

  bool result = false;
  switch (keycode) {
    case LOWER:
      update_change_layer(record->event.pressed, _LOWER, _RAISE, _ADJUST);
      break;
    case RAISE:
      update_change_layer(record->event.pressed, _RAISE, _LOWER, _ADJUST);
      break;
    case BASE:
      if (record->event.pressed) {
        default_layer_set(L_BASE);
      }
      break;
    case BASES:
      if (record->event.pressed) {
        default_layer_set(L_BASES);
      }
      break;
    case LOWRS:
      update_change_layer(record->event.pressed, _LOWRS, _RAISE, _ADJUST);
      break;
    case KANJI:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui == false) {
          register_code(KC_LANG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      break;
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  UPDATE_KEYMAP_STATUS();
  return result;
}
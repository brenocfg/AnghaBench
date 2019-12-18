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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  BACKLIT 132 
#define  DATA 131 
 int /*<<< orphan*/  KC_RSFT ; 
#define  LOWER 130 
#define  QWERTY 129 
#define  RAISE 128 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _DATA ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  breathing_enable () ; 
 int /*<<< orphan*/  breathing_self_disable () ; 
 int /*<<< orphan*/  default_layer_state ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        #ifdef BACKLIGHT_BREATHING
          breathing_self_disable();
        #endif
      }
      return false;
      break;
    case DATA:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DATA);
        #ifdef BACKLIGHT_BREATHING
          breathing_enable();
        #endif
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        uint8_t default_layer = biton32(default_layer_state);
        if (default_layer == _QWERTY) {
          #ifdef BACKLIGHT_BREATHING
            breathing_enable();
          #endif
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        uint8_t default_layer = biton32(default_layer_state);
        if (default_layer == _QWERTY) {
          #ifdef BACKLIGHT_BREATHING
            breathing_self_disable();
          #endif
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        uint8_t default_layer = biton32(default_layer_state);
        if (default_layer == _QWERTY) {
          #ifdef BACKLIGHT_BREATHING
            breathing_enable();
          #endif
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        uint8_t default_layer = biton32(default_layer_state);
        if (default_layer == _QWERTY) {
          #ifdef BACKLIGHT_BREATHING
            breathing_self_disable();
          #endif
        }
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_BREATHING
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}
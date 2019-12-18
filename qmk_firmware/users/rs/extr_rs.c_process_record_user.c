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
typedef  int uint16_t ;
struct TYPE_6__ {scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_0 ; 
 int /*<<< orphan*/  KC_9 ; 
 int /*<<< orphan*/  KC_COMM ; 
 int /*<<< orphan*/  KC_DOT ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RSFT ; 
#define  LPLT 132 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
#define  NEQL 131 
#define  RGBRST 130 
#define  RGB_MOD 129 
#define  RPGT 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  eeconfig_update_rgblight_default () ; 
 int get_mods () ; 
 int /*<<< orphan*/  keylog_set_keymap (int,TYPE_2__*) ; 
 int process_record_keymap (int,TYPE_2__*) ; 
 int /*<<< orphan*/  register_mods (int) ; 
 int /*<<< orphan*/  rgb_mod_changed_keymap () ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_step () ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    keylog_set_keymap(keycode, record);
  }

  switch (keycode) {
  case NEQL: // !=
    if (record->event.pressed) {
      SEND_STRING("!=");
    }
    return false;
  case LPLT: // ( or < with shift
    if (record->event.pressed) {
      if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
        // <
        tap_code(KC_COMM); // shift is already registered
      } else {
        // (
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_9);
        unregister_mods(MOD_BIT(KC_LSFT));
      }
    }
    return false;
  case RPGT: // ) or > with shift
    if (record->event.pressed) {
      if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
        // <
        tap_code(KC_DOT); // shift is already registered
      } else {
        // )
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_0);
        unregister_mods(MOD_BIT(KC_LSFT));
      }
    }
    return false;
#ifdef RGBLIGHT_ENABLE
  case RGB_MOD:
      if (record->event.pressed) {
        rgblight_step();
        rgb_mod_changed_keymap();
      }
    return false;
  case RGBRST:
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
        rgb_mod_changed_keymap();
      }
    return false;
#endif
  }
  return process_record_keymap(keycode, record);
}
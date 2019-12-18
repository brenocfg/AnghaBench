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
struct TYPE_7__ {int mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  KC_END ; 
 int /*<<< orphan*/  KC_HOME ; 
 int /*<<< orphan*/  KC_INS ; 
 int /*<<< orphan*/  KC_LSFT ; 
#define  KC_NLCK 133 
#define  KC_NO 132 
#define  KC_PENT 131 
 int /*<<< orphan*/  KC_PGDN ; 
 int /*<<< orphan*/  KC_PGUP ; 
#define  KC_PPLS 130 
 int /*<<< orphan*/  KC_RSFT ; 
#define  KC_TRNS 129 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ONESHOT_OTHER_KEY_PRESSED ; 
 int /*<<< orphan*/  ONESHOT_START ; 
#define  RESET 128 
 int /*<<< orphan*/  clear_oneshot_layer_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_oneshot_layer_active () ; 
 TYPE_4__* keyboard_report ; 
 int layer_state ; 
 int /*<<< orphan*/  numlock_on ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case RESET:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    case KC_PPLS:
      if (!numlock_on) {
        if (is_oneshot_layer_active() || layer_state & 0x2) {
          if (record->event.pressed)
            register_code(KC_HOME);
          else
            unregister_code(KC_HOME);
          clear_oneshot_layer_state(ONESHOT_START);
        }
        else {
          if (record->event.pressed)
            register_code(KC_PGUP);
          else
            unregister_code(KC_PGUP);
        }
        return false;
      }
      return true;
    case KC_PENT:
      if (!numlock_on) {
        if (is_oneshot_layer_active() || layer_state & 0x2) {
          if (record->event.pressed)
            register_code(KC_END);
          else
            unregister_code(KC_END);
          clear_oneshot_layer_state(ONESHOT_START);
        }
        else {
          if (record->event.pressed)
            register_code(KC_PGDN);
          else
            unregister_code(KC_PGDN);
        }
        return false;
      }
      return true;
    case KC_NLCK:
      /* Shift + NumLock will be treated as shift-Insert */
      if ((keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT))) {
        if (record->event.pressed) {
          register_code(KC_INS);
          unregister_code(KC_INS);
        }
        return false;
      }
      else
        return true;
    default:
      return true;
  }
  return true;
}
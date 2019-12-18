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
 int /*<<< orphan*/  CHECK_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CLEAR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  FUN_LAY 131 
#define  MOU_TOG 130 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_UP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOGGLE_BIT (int /*<<< orphan*/ ,int) ; 
#define  WIN_KEY 129 
#define  WIN_LCK 128 
 int /*<<< orphan*/  X_LGUI ; 
 int /*<<< orphan*/  _FUNC ; 
 int /*<<< orphan*/  _MOUSE ; 
 int /*<<< orphan*/  keyboard_state ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    // acts like a momentary function layer press
    case FUN_LAY:
      if (record->event.pressed) { 
        layer_on(_FUNC);
        if (CHECK_BIT(keyboard_state, 1)) {
          layer_on(_MOUSE);
        } 
        else {
          layer_off(_MOUSE);
        }
        // turns on function layer status
        SET_BIT(keyboard_state, 0);
      }
      // key released
      else {
        layer_off(_FUNC);
        layer_off(_MOUSE);
        // turns off function layer status
        CLEAR_BIT(keyboard_state, 0);
      }
      break;

    case MOU_TOG:
      if(record->event.pressed) {
        // toggles navigation layer state
        TOGGLE_BIT(keyboard_state, 1);

        // if FN is pressed down while hitting this key, the correct layer will be updated,
        // so that the FN key doesn't need to be pressed down again to start using the functionality
        if (CHECK_BIT(keyboard_state, 0)) {
          if (CHECK_BIT(keyboard_state, 1)) {
            layer_on(_MOUSE);
          }
          else {
            layer_off(_MOUSE);
          } 
        }
      }
      break;

    case WIN_LCK:
      if (record->event.pressed) {
        // toggles windows key lock state
        TOGGLE_BIT(keyboard_state, 2);
      }
      break;

    // uses seperate WIN_KEY so that WIN_LCK does not affect Mac Layer's KC_LGUI
    case WIN_KEY:
      // checks if windows key lock is off to allow key to be pressed
      if (!CHECK_BIT(keyboard_state, 2)) {
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LGUI));
          return false;
        }
        // key released
        else { 
          SEND_STRING(SS_UP(X_LGUI));
          return false;
        }
      }
      break;
  }
  return true;
}
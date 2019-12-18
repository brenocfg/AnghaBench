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
#define  COLEMAK 134 
#define  KC_BSDEL 133 
 int /*<<< orphan*/  KC_BSLASH ; 
 int /*<<< orphan*/  KC_BSLS ; 
 int /*<<< orphan*/  KC_BSPC ; 
 int /*<<< orphan*/  KC_COMM ; 
#define  KC_CPIPE 132 
 int /*<<< orphan*/  KC_DEL ; 
 int /*<<< orphan*/  KC_DOT ; 
#define  KC_DOTQ 131 
#define  KC_FBSLH 130 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_LSHIFT ; 
#define  KC_LYDEF 129 
 int /*<<< orphan*/  KC_RSHIFT ; 
 int /*<<< orphan*/  KC_SLSH ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
#define  QWERTY 128 
 int /*<<< orphan*/  _COLEMAK ; 
 int /*<<< orphan*/  _QWERTY ; 
 TYPE_4__* keyboard_report ; 
 int /*<<< orphan*/  layer_clear () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int shift ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {
    case KC_LYDEF:
      layer_clear();
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case KC_BSDEL:
      if (record->event.pressed) {
        if (keyboard_report->mods & shift) {
          if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
            unregister_code(KC_LSHIFT);
          }
          else {
            unregister_code(KC_RSHIFT);
          }
          register_code(KC_DEL);
        }
        else {
          register_code(KC_BSPC);
        }
      }
      else {
        unregister_code(KC_DEL);
        unregister_code (KC_BSPC);
      }
      return false;
      break;
    case KC_FBSLH:
      if (record->event.pressed) {
        if (keyboard_report->mods & shift) {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
              unregister_code(KC_LSHIFT);
            }
            else {
              unregister_code(KC_RSHIFT);
            }
          register_code(KC_BSLASH);
        }
        else {
          register_code(KC_SLSH);
        }
      }
      else {
        unregister_code(KC_BSLASH);
        unregister_code (KC_SLSH);
      }
      return false;
      break;
    case KC_DOTQ:
      if (record->event.pressed) {
        if (keyboard_report->mods & shift) {
          register_code(KC_SLSH); // shifted slash = ?
        }
        else {
          register_code(KC_DOT);
        }
      }
      else {
        unregister_code(KC_SLSH); // shifted slash = ?
        unregister_code (KC_DOT);
      }
      return false;
      break;
    case KC_CPIPE:
      if (record->event.pressed) {
        if (keyboard_report->mods & shift) {
          register_code(KC_BSLS);
        }
        else {
          register_code(KC_COMM);
        }
      }
      else {
        unregister_code(KC_BSLS);
        unregister_code (KC_COMM);
      }
      return false;
      break;
    }
    return true;
}
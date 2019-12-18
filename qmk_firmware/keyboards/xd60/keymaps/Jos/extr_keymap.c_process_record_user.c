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
 int /*<<< orphan*/  KC_7 ; 
 int /*<<< orphan*/  KC_8 ; 
 int /*<<< orphan*/  KC_APP ; 
 int /*<<< orphan*/  KC_BSLS ; 
#define  KC_BSPC 137 
 int /*<<< orphan*/  KC_CAPS ; 
#define  KC_DEL 136 
#define  KC_ENT 135 
#define  KC_EQL 134 
#define  KC_ESC 133 
#define  KC_LSFT 132 
#define  KC_MINS 131 
#define  KC_RALT 130 
#define  KC_RCTRL 129 
#define  KC_RSFT 128 
 int /*<<< orphan*/  del_blocked ; 
 int /*<<< orphan*/  register_code (int const) ; 
 int special_mods (int /*<<< orphan*/ ,TYPE_2__*,int const) ; 
 int /*<<< orphan*/  unregister_code (int const) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode){
    #ifdef ISOLIKE_ALT_ENTER
    // RALT + ENT is the same as RALT+BSLS. 
    // For logical placement of *{* and *}* (the former being RALT+BSLS) with ANSI enter on 
    // ISO-based Canadian Multilingual layout (or any other ISO layout on ANSI keyboards).
    case KC_ENT:    return special_mods(KC_BSLS, record, KC_RALT);  // RALT + ENT -> RALT + BSLS            // See comment above
    #endif
    #ifdef TWO_SFT_CAPS
    case KC_LSFT:   return special_mods(KC_CAPS, record, KC_RSFT);  // Both shifts together -> Caps Lock    // RSFT  pressed first case
    case KC_RSFT:   return special_mods(KC_CAPS, record, KC_LSFT);  // Both shifts together -> Caps Lock    // LSFT  pressed first case
    #endif
    #ifdef APP_IS_RALT_RCTRL
    case KC_RCTRL:  return special_mods(KC_APP,  record, KC_RALT);  // RALT + RCTRL -> APP                  // RCTRL pressed first case
    case KC_RALT:   return special_mods(KC_APP,  record, KC_RCTRL); // RALT + RCTRL -> APP                  // RALT  pressed first case
    #endif
    #ifdef ALT_MINSEQL_IS_ALT_78
    case KC_MINS:  return special_mods(KC_7,  record, KC_RALT); // RALT + MINS -> RALT+7                  // {} in CAN Mult. softawre layout
    case KC_EQL:   return special_mods(KC_8,  record, KC_RALT); // RALT + EQL  -> RALT+8                  // ½¬ normally... Less finger stretch.
    #endif
    #ifdef HELD_ESC_IS_SHIFT
    case KC_ESC:    // Physically *ESC* is *CAPS*                   // Holding ESC -> SHIFT  (0 delay)      // Less awkward *<ESC>:wq* in vim
      if (record->event.pressed) {
        register_code(KC_ESC);      // Tapping ESC
        unregister_code(KC_ESC);
        register_code(KC_LSFT);     // Holding LSFT
        return false;
      } else {
        unregister_code(KC_LSFT);   // Releasing LSFT
        return false;
      }
    #endif
    #ifdef BSPC_BLOCKS_DEL
    // If BSPC is held, we flag DEL as disabled. To avoids acidental presses of DEL with split backspace key.
    case KC_BSPC:
      del_blocked = record->event.pressed;
      return true;
    // We don't handle DEL if it is pressed and flagged as disabled
    case KC_DEL:
      if (del_blocked && record->event.pressed) {
        return false;
      } else {
        return true;
      }
    #endif
    default: return true;   // Let QMK handle the rest as usual
  }
}
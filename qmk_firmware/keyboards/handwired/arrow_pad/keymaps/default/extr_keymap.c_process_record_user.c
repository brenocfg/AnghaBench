#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {int count; } ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {TYPE_2__ tap; TYPE_1__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_PENT ; 
 int /*<<< orphan*/  KC_X ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
#define  M_COPY 130 
#define  M_CTALT 129 
#define  M_SHFCT 128 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  // MACRODOWN only works in this function
  switch (keycode) {

  case M_COPY:
    if (record->event.pressed) {
      register_code(KC_LCTL);
      if (record->tap.count == 1) {
        register_code(KC_C);
        unregister_code(KC_C);
      } else if (record->tap.count == 2) {
        register_code(KC_X);
        unregister_code(KC_X);
      }
      unregister_code(KC_LCTL);
    }
    break;

  case M_SHFCT:
    if (record->event.pressed) {
      if (record->tap.count <= 2) register_mods(MOD_BIT(KC_LSFT));
      if (record->tap.count == 2) register_mods(MOD_BIT(KC_LCTL));
      if (record->tap.count == 3) register_code(KC_PENT);;
    } else {
      unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LCTL));
      unregister_code(KC_PENT);
    }
    break;

  case M_CTALT:
    if (record->event.pressed) {
      if (record->tap.count < 2) register_mods(MOD_BIT(KC_LCTL));
      if (record->tap.count >= 2) register_mods(MOD_BIT(KC_LALT));
    } else {
      unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
    }
    break;
  }

  return true;
}
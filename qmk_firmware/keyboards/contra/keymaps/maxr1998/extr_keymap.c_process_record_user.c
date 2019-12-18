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
 int /*<<< orphan*/  DE_SS ; 
#define  KC_BSPC 130 
 int /*<<< orphan*/  KC_LSFT ; 
#define  KC_N3 129 
#define  KC_NR 128 
 int /*<<< orphan*/  KC_RSFT ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _NR ; 
 int /*<<< orphan*/  _NR_L3 ; 
 int get_mods () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer_user () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_BSPC:
      if (record->event.pressed) {
        if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
          register_code(DE_SS);
          return false;
        }
      } else {
        unregister_code(DE_SS);
      }
      return true;
    case KC_NR:
      if (record->event.pressed) {
        layer_on(_NR);
      } else {
        layer_off(_NR);
      }
      update_tri_layer_user();
      return false;
    case KC_N3:
      if (record->event.pressed) {
        layer_on(_NR_L3);
      } else {
        layer_off(_NR_L3);
      }
      update_tri_layer_user();
      return false;
    default:
      return true;
  }
}
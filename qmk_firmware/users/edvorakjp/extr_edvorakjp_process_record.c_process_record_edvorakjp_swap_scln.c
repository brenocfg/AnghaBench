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
typedef  int const uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RSFT ; 
 scalar_t__ KC_SCLN ; 
 int const MOD_BIT (int /*<<< orphan*/ ) ; 
 int get_mods () ; 
 int /*<<< orphan*/  set_mods (int const) ; 

bool process_record_edvorakjp_swap_scln(uint16_t keycode, keyrecord_t *record) {
#ifdef SWAP_SCLN
  static const uint8_t shift_bits = MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT);
  static uint8_t last_mods_status;
  if (keycode == KC_SCLN) {
    if (record->event.pressed) {
      last_mods_status = get_mods();

      // invert shift_bits
      if (last_mods_status & shift_bits) {
        set_mods(last_mods_status & ~shift_bits);
      } else {
        set_mods(last_mods_status | MOD_BIT(KC_LSFT));
      }
    } else {
      set_mods(last_mods_status);
      last_mods_status = 0;
    }
  }
#endif
  return true;
}
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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ count; scalar_t__ interrupted; } ;
struct TYPE_5__ {scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_2__ tap; TYPE_1__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_weak_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_weak_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_keyboard_report () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

void tap_helper(keyrecord_t *record, uint16_t orig_mod, uint16_t macro_mod, uint16_t macro_kc ) {
  if (record->event.pressed) {
      if (record->tap.count > 0 && !record->tap.interrupted) {
          if (record->tap.interrupted) {
              register_mods(MOD_BIT(orig_mod));
          }
      } else {
          register_mods(MOD_BIT(orig_mod));
      }
  } else {
      if (record->tap.count > 0 && !(record->tap.interrupted)) {
          add_weak_mods(MOD_BIT(macro_mod));
          send_keyboard_report();
          register_code(macro_kc);
          unregister_code(macro_kc);
          del_weak_mods(MOD_BIT(macro_mod));
          send_keyboard_report();
          record->tap.count = 0;  // ad hoc: cancel tap
      } else {
          unregister_mods(MOD_BIT(orig_mod));
      }
  }
}
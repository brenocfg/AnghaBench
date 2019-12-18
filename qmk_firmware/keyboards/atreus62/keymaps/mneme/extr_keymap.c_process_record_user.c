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
#define  KC_ESC 128 
 int /*<<< orphan*/  clear_oneshot_mods () ; 
 int /*<<< orphan*/  get_oneshot_mods () ; 
 int /*<<< orphan*/  has_oneshot_mods_timed_out () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool queue = true;

  //Cancle one-shot mods.
  switch (keycode) {
    case KC_ESC:
      if (record->event.pressed && get_oneshot_mods() && !has_oneshot_mods_timed_out()) {
        clear_oneshot_mods();
        queue = false;
      }
      break;
  }
  return queue;
}
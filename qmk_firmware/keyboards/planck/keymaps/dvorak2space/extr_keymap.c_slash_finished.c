#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qk_tap_dance_state_t ;

/* Variables and functions */
#define  DOUBLE_TAP 129 
 int /*<<< orphan*/  KC_NUBS ; 
 int /*<<< orphan*/  KC_SLSH ; 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  clear_mods () ; 
 int /*<<< orphan*/  clear_weak_mods () ; 
 int cur_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

void slash_finished(qk_tap_dance_state_t *state, void *user_data) {
  int td_state = cur_dance(state);
  switch(td_state) {
    case SINGLE_TAP:
      clear_mods();
      clear_weak_mods();
      tap_code(KC_SLSH);
      break;
    case DOUBLE_TAP:
      tap_code(KC_NUBS);
  }
}
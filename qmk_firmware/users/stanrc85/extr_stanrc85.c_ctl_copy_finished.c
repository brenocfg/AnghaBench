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
#define  DOUBLE_TAP 130 
 int /*<<< orphan*/  KC_RCTL ; 
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  SS_LCTRL (char*) ; 
 int cur_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int td_state ; 

void ctl_copy_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      SEND_STRING(SS_LCTRL("c"));
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL));
      break;
    case DOUBLE_TAP:
      SEND_STRING(SS_LCTRL("v"));
  }
}
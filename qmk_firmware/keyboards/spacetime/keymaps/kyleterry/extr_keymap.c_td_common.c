#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_INS ; 
 int /*<<< orphan*/  KC_O ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 

void td_common(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      /* this case handles ctrl+o which is my tmux prefix
       */
      tap_code16(C(KC_O));
      reset_tap_dance(state);
      break;
    case 2:
      /* this case handles shift+insert which is a common way
       * for me to paste text in linux
       */
      tap_code16(S(KC_INS));
      reset_tap_dance(state);
      break;
  }
}
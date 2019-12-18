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
struct TYPE_4__ {int count; scalar_t__ pressed; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOLD_CTRL ; 
 int /*<<< orphan*/  KC_BSPC ; 
 int /*<<< orphan*/  KC_LCTRL ; 
 TYPE_2__ fib_bspc ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 

void dance_backspace_ended (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->pressed) {
      fib_bspc.state = HOLD_CTRL;
      register_code(KC_LCTRL);
    } else {
      register_code(KC_BSPC);
    }
  }
}
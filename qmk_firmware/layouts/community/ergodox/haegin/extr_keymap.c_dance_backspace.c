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
struct TYPE_5__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;
struct TYPE_6__ {int b; scalar_t__ a; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPC_WORD ; 
 int /*<<< orphan*/  KC_BSPC ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  cur_backspace (TYPE_1__*) ; 
 TYPE_2__ fib_bspc ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 

void dance_backspace (qk_tap_dance_state_t *state, void *user_data) {
  // If we're at the fifth tap, switch to deleting by words, and reset the fib
  // counter
  if (state->count == 4) {
    register_code(KC_LALT);
    fib_bspc.state = BSPC_WORD;
    fib_bspc.a = 0;
    fib_bspc.b = 1;
  }
  // If we're on the first press, wait to find out if it's being held
  // If we're on the second tap, process the first tap, because we're past
  // holding for ctrl now, then act normally
  if (state->count == 2) {
    register_code(KC_BSPC);
  }
  if (state->count > 1) {
    cur_backspace(state);
  }
}
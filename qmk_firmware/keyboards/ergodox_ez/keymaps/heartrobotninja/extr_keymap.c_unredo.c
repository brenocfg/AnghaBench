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
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_Y ; 
 int /*<<< orphan*/  KC_Z ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void unredo(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_Y);
    unregister_code(KC_Y);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_Z);
    unregister_code(KC_Z);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}
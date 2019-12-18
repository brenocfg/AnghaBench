#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_GRV ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_SLSH ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void tilde_reset(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count == 2) {
    unregister_code(KC_SLSH);
  } else {
    unregister_code(KC_GRV);
    unregister_code(KC_LSFT);
  }
}
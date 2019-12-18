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
struct TYPE_4__ {int count; int finished; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  kc2; } ;
typedef  TYPE_2__ qk_tap_dance_pair_t ;

/* Variables and functions */
 int /*<<< orphan*/  register_code16 (int /*<<< orphan*/ ) ; 

void qk_tap_dance_pair_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 2) {
        register_code16(pair->kc2);
        state->finished = true;
    }
}
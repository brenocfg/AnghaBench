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
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  layer; int /*<<< orphan*/  kc; } ;
typedef  TYPE_2__ qk_tap_dance_dual_role_t ;

/* Variables and functions */
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void td_mod_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *data = (qk_tap_dance_dual_role_t *)user_data;

    if (state->count == 1 || state->count >= 3) {
        unregister_code(data->kc);
    }
    if (state->count >= 2) {
        layer_off(data->layer);
    }
}
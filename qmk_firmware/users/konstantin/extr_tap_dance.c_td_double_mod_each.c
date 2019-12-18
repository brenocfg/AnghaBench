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
struct TYPE_4__ {int count; int weak_mods; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  kc2; int /*<<< orphan*/  kc1; } ;
typedef  TYPE_2__ qk_tap_dance_pair_t ;

/* Variables and functions */
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void td_double_mod_each(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *data = (qk_tap_dance_pair_t *)user_data;

    // Single tap → mod1, double tap → mod2, triple tap etc. → mod1+mod2
    if (state->count == 1 || state->count == 3) {
        register_code(data->kc1);
    } else if (state->count == 2) {
        unregister_code(data->kc1);
        register_code(data->kc2);
    }
    // Prevent tap dance from sending the mods as weak mods
    state->weak_mods &= ~(MOD_BIT(data->kc1) | MOD_BIT(data->kc2));
}
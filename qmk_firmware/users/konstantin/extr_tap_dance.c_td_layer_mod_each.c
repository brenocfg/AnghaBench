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
struct TYPE_5__ {int started; int /*<<< orphan*/  kc; int /*<<< orphan*/  layer; int /*<<< orphan*/  layer_on; } ;
typedef  TYPE_2__ qk_tap_dance_layer_mod_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 

void td_layer_mod_each(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_layer_mod_t *data = (qk_tap_dance_layer_mod_t *)user_data;
    if (!data->started) {
        data->layer_on = IS_LAYER_ON(data->layer);
        data->started = true;
    }

    // Single tap → layer, double tap → mod, triple tap etc. → layer+mod
    if (state->count == 1 || state->count == 3) {
        layer_on(data->layer);
    } else if (state->count == 2) {
        if (!data->layer_on) {
            layer_off(data->layer);
        }
        register_code(data->kc);
    }
}
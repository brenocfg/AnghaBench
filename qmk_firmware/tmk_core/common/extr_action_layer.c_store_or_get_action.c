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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  keypos_t ;
typedef  int /*<<< orphan*/  action_t ;

/* Variables and functions */
 int /*<<< orphan*/  action_for_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ disable_action_cache ; 
 int /*<<< orphan*/  layer_switch_get_action (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_switch_get_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_source_layers_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_source_layers_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

action_t store_or_get_action(bool pressed, keypos_t key) {
#if !defined(NO_ACTION_LAYER) && !defined(STRICT_LAYER_RELEASE)
    if (disable_action_cache) {
        return layer_switch_get_action(key);
    }

    uint8_t layer;

    if (pressed) {
        layer = layer_switch_get_layer(key);
        update_source_layers_cache(key, layer);
    } else {
        layer = read_source_layers_cache(key);
    }
    return action_for_key(layer, key);
#else
    return layer_switch_get_action(key);
#endif
}
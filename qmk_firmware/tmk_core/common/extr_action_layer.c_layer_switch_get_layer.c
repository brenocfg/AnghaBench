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
typedef  unsigned long uint8_t ;
typedef  unsigned long layer_state_t ;
typedef  int /*<<< orphan*/  keypos_t ;
typedef  unsigned long int8_t ;
struct TYPE_3__ {scalar_t__ code; } ;
typedef  TYPE_1__ action_t ;

/* Variables and functions */
 scalar_t__ ACTION_TRANSPARENT ; 
 TYPE_1__ action_for_key (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long default_layer_state ; 
 unsigned long get_highest_layer (unsigned long) ; 
 unsigned long layer_state ; 

uint8_t layer_switch_get_layer(keypos_t key) {
#ifndef NO_ACTION_LAYER
    action_t action;
    action.code = ACTION_TRANSPARENT;

    layer_state_t layers = layer_state | default_layer_state;
    /* check top layer first */
    for (int8_t i = sizeof(layer_state_t) * 8 - 1; i >= 0; i--) {
        if (layers & (1UL << i)) {
            action = action_for_key(i, key);
            if (action.code != ACTION_TRANSPARENT) {
                return i;
            }
        }
    }
    /* fall back to layer 0 */
    return 0;
#else
    return get_highest_layer(default_layer_state);
#endif
}
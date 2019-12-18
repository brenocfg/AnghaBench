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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t NUMBER_OF_DIP_SWITCHES ; 
 int /*<<< orphan*/ * dip_switch_pad ; 
 size_t* dip_switch_state ; 
 int /*<<< orphan*/  dip_switch_update_kb (size_t,size_t) ; 
 int /*<<< orphan*/  dip_switch_update_mask_kb (size_t) ; 
 size_t* last_dip_switch_state ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  readPin (int /*<<< orphan*/ ) ; 

void dip_switch_read(bool forced) {
    bool     has_dip_state_changed = false;
    uint32_t dip_switch_mask       = 0;

    for (uint8_t i = 0; i < NUMBER_OF_DIP_SWITCHES; i++) {
        dip_switch_state[i] = !readPin(dip_switch_pad[i]);
        dip_switch_mask |= dip_switch_state[i] << i;
        if (last_dip_switch_state[i] ^ dip_switch_state[i] || forced) {
            has_dip_state_changed = true;
            dip_switch_update_kb(i, dip_switch_state[i]);
        }
    }
    if (has_dip_state_changed) {
        dip_switch_update_mask_kb(dip_switch_mask);
    }
    memcpy(last_dip_switch_state, dip_switch_state, sizeof(&dip_switch_state));
}
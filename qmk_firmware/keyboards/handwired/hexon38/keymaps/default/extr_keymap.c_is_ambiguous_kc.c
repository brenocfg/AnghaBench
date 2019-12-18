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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ mod_config (int) ; 

bool is_ambiguous_kc(uint16_t kc) {
    // See the MT() define: https://github.com/qmk/qmk_firmware/blob/master/quantum/quantum_keycodes.h#L642
    // See the QK_MOD_TAP case: https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_common.c#L134
    uint8_t mod = mod_config((kc >> 0x8) & 0x1F);
    return mod != 0;
}
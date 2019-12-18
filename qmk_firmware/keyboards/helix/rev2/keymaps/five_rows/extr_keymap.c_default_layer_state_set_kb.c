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
typedef  int uint32_t ;

/* Variables and functions */
 int current_default_layer ; 

uint32_t default_layer_state_set_kb(uint32_t state) {
    // 1<<_QWERTY  - 1 == 1 - 1 == _QWERTY (=0)
    // 1<<_COLEMAK - 1 == 2 - 1 == _COLEMAK (=1)
    current_default_layer = state - 1;
    // 1<<_DVORAK  - 2 == 4 - 2 == _DVORAK (=2)
    if ( current_default_layer == 3 ) current_default_layer -= 1;
    // 1<<_EUCALYN - 5 == 8 - 5 == _EUCALYN (=3)
    if ( current_default_layer == 7 ) current_default_layer -= 4;
    // 1<<_KEYPAD  - 12 == 16 - 12 == _KEYPAD (=4)
    if ( current_default_layer == 15 ) current_default_layer -= 11;
    return state;
}
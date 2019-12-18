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
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  clear_keyboard_but_mods () ; 
 int /*<<< orphan*/  clear_keyboard_but_mods_and_keys () ; 
 int /*<<< orphan*/  dprint (char*) ; 
 int /*<<< orphan*/  dprintln () ; 
 int /*<<< orphan*/  layer_debug () ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  layer_state_set_kb (int /*<<< orphan*/ ) ; 

void layer_state_set(layer_state_t state) {
    state = layer_state_set_kb(state);
    dprint("layer_state: ");
    layer_debug();
    dprint(" to ");
    layer_state = state;
    layer_debug();
    dprintln();
#    ifdef STRICT_LAYER_RELEASE
    clear_keyboard_but_mods();  // To avoid stuck keys
#    else
    clear_keyboard_but_mods_and_keys();  // Don't reset held keys
#    endif
}
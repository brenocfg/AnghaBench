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
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  default_layer_debug () ; 
 int /*<<< orphan*/  default_layer_state ; 
 int /*<<< orphan*/  default_layer_state_set_kb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void default_layer_state_set(layer_state_t state) {
    state = default_layer_state_set_kb(state);
    debug("default_layer_state: ");
    default_layer_debug();
    debug(" to ");
    default_layer_state = state;
    default_layer_debug();
    debug("\n");
#ifdef STRICT_LAYER_RELEASE
    clear_keyboard_but_mods();  // To avoid stuck keys
#else
    clear_keyboard_but_mods_and_keys();  // Don't reset held keys
#endif
}
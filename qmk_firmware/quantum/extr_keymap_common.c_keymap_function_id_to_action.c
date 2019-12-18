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
typedef  size_t uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/ * fn_actions ; 
 size_t pgm_read_word (int /*<<< orphan*/ *) ; 

__attribute__((weak)) uint16_t keymap_function_id_to_action(uint16_t function_id) {
// The compiler sees the empty (weak) fn_actions and generates a warning
// This function should not be called in that case, so the warning is too strict
// If this function is called however, the keymap should have overridden fn_actions, and then the compile
// is comparing against the wrong array
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
    return pgm_read_word(&fn_actions[function_id]);
#pragma GCC diagnostic pop
}
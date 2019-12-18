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
typedef  int /*<<< orphan*/  keyrecord_t ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DYNAMIC_MACRO_CURRENT_SLOT () ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dynamic_macro_play_user (scalar_t__) ; 
 int /*<<< orphan*/  layer_clear () ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  process_record (int /*<<< orphan*/ *) ; 

void dynamic_macro_play(keyrecord_t *macro_buffer, keyrecord_t *macro_end, int8_t direction) {
    dprintf("dynamic macro: slot %d playback\n", DYNAMIC_MACRO_CURRENT_SLOT());

    layer_state_t saved_layer_state = layer_state;

    clear_keyboard();
    layer_clear();

    while (macro_buffer != macro_end) {
        process_record(macro_buffer);
        macro_buffer += direction;
    }

    clear_keyboard();

    layer_state = saved_layer_state;

    dynamic_macro_play_user(direction);
}
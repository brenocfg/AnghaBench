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

/* Variables and functions */
 int /*<<< orphan*/  input_handler_for_each_handle (int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_handler ; 
 int /*<<< orphan*/  kbd_update_leds_helper ; 

__attribute__((used)) static void kbd_propagate_led_state(unsigned int old_state,
				    unsigned int new_state)
{
	input_handler_for_each_handle(&kbd_handler, &new_state,
				      kbd_update_leds_helper);
}
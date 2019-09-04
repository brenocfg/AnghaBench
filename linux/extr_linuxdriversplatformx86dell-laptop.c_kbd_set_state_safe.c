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
struct kbd_state {int dummy; } ;

/* Variables and functions */
 int kbd_set_state (struct kbd_state*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int kbd_set_state_safe(struct kbd_state *state, struct kbd_state *old)
{
	int ret;

	ret = kbd_set_state(state);
	if (ret == 0)
		return 0;

	/*
	 * When setting the new state fails,try to restore the previous one.
	 * This is needed on some machines where BIOS sets a default state when
	 * setting a new state fails. This default state could be all off.
	 */

	if (kbd_set_state(old))
		pr_err("Setting old previous keyboard state failed\n");

	return ret;
}
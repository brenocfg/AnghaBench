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
 int console_locked ; 
 int console_may_schedule ; 
 scalar_t__ console_suspended ; 
 int /*<<< orphan*/  down_console_sem () ; 
 int /*<<< orphan*/  might_sleep () ; 

void console_lock(void)
{
	might_sleep();

	down_console_sem();
	if (console_suspended)
		return;
	console_locked = 1;
	console_may_schedule = 1;
}
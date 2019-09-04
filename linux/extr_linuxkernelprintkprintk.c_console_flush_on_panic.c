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
 scalar_t__ console_may_schedule ; 
 int /*<<< orphan*/  console_trylock () ; 
 int /*<<< orphan*/  console_unlock () ; 

void console_flush_on_panic(void)
{
	/*
	 * If someone else is holding the console lock, trylock will fail
	 * and may_schedule may be set.  Ignore and proceed to unlock so
	 * that messages are flushed out.  As this can be called from any
	 * context and we don't want to get preempted while flushing,
	 * ensure may_schedule is cleared.
	 */
	console_trylock();
	console_may_schedule = 0;
	console_unlock();
}
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
 int /*<<< orphan*/  debug_locks_off () ; 
 int /*<<< orphan*/  logbuf_lock ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  printk_safe_flush () ; 
 scalar_t__ raw_spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

void printk_safe_flush_on_panic(void)
{
	/*
	 * Make sure that we could access the main ring buffer.
	 * Do not risk a double release when more CPUs are up.
	 */
	if (raw_spin_is_locked(&logbuf_lock)) {
		if (num_online_cpus() > 1)
			return;

		debug_locks_off();
		raw_spin_lock_init(&logbuf_lock);
	}

	printk_safe_flush();
}
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
 int /*<<< orphan*/  HZ ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cond_resched_tasks_rcu_qs () ; 
 int round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  stutter_pause_test ; 
 int /*<<< orphan*/  torture_shutdown_absorb (char const*) ; 

bool stutter_wait(const char *title)
{
	int spt;
	bool ret = false;

	cond_resched_tasks_rcu_qs();
	spt = READ_ONCE(stutter_pause_test);
	for (; spt; spt = READ_ONCE(stutter_pause_test)) {
		ret = true;
		if (spt == 1) {
			schedule_timeout_interruptible(1);
		} else if (spt == 2) {
			while (READ_ONCE(stutter_pause_test))
				cond_resched();
		} else {
			schedule_timeout_interruptible(round_jiffies_relative(HZ));
		}
		torture_shutdown_absorb(title);
	}
	return ret;
}
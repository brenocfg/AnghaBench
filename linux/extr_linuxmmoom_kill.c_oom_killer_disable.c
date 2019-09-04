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
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int oom_killer_disabled ; 
 int /*<<< orphan*/  oom_killer_enable () ; 
 int /*<<< orphan*/  oom_lock ; 
 int /*<<< orphan*/  oom_victims ; 
 int /*<<< orphan*/  oom_victims_wait ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,long) ; 

bool oom_killer_disable(signed long timeout)
{
	signed long ret;

	/*
	 * Make sure to not race with an ongoing OOM killer. Check that the
	 * current is not killed (possibly due to sharing the victim's memory).
	 */
	if (mutex_lock_killable(&oom_lock))
		return false;
	oom_killer_disabled = true;
	mutex_unlock(&oom_lock);

	ret = wait_event_interruptible_timeout(oom_victims_wait,
			!atomic_read(&oom_victims), timeout);
	if (ret <= 0) {
		oom_killer_enable();
		return false;
	}
	pr_info("OOM killer disabled.\n");

	return true;
}
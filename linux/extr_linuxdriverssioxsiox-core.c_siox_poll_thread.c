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
struct siox_master {unsigned long last_poll; unsigned long poll_interval; scalar_t__ active; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_IDLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 long jiffies ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siox_master_lock (struct siox_master*) ; 
 int /*<<< orphan*/  siox_master_unlock (struct siox_master*) ; 
 int /*<<< orphan*/  siox_poll (struct siox_master*) ; 
 scalar_t__ time_is_before_eq_jiffies (unsigned long) ; 

__attribute__((used)) static int siox_poll_thread(void *data)
{
	struct siox_master *smaster = data;
	signed long timeout = 0;

	get_device(&smaster->dev);

	for (;;) {
		if (kthread_should_stop()) {
			put_device(&smaster->dev);
			return 0;
		}

		siox_master_lock(smaster);

		if (smaster->active) {
			unsigned long next_poll =
				smaster->last_poll + smaster->poll_interval;
			if (time_is_before_eq_jiffies(next_poll))
				siox_poll(smaster);

			timeout = smaster->poll_interval -
				(jiffies - smaster->last_poll);
		} else {
			timeout = MAX_SCHEDULE_TIMEOUT;
		}

		/*
		 * Set the task to idle while holding the lock. This makes sure
		 * that we don't sleep too long when the bus is reenabled before
		 * schedule_timeout is reached.
		 */
		if (timeout > 0)
			set_current_state(TASK_IDLE);

		siox_master_unlock(smaster);

		if (timeout > 0)
			schedule_timeout(timeout);

		/*
		 * I'm not clear if/why it is important to set the state to
		 * RUNNING again, but it fixes a "do not call blocking ops when
		 * !TASK_RUNNING;"-warning.
		 */
		set_current_state(TASK_RUNNING);
	}
}
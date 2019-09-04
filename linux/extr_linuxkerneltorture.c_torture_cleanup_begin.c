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
 int /*<<< orphan*/  FULLSTOP_RMMOD ; 
 scalar_t__ FULLSTOP_SHUTDOWN ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fullstop ; 
 int /*<<< orphan*/  fullstop_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  torture_onoff_cleanup () ; 
 int /*<<< orphan*/  torture_shuffle_cleanup () ; 
 int /*<<< orphan*/  torture_shutdown_cleanup () ; 
 int /*<<< orphan*/  torture_stutter_cleanup () ; 

bool torture_cleanup_begin(void)
{
	mutex_lock(&fullstop_mutex);
	if (READ_ONCE(fullstop) == FULLSTOP_SHUTDOWN) {
		pr_warn("Concurrent rmmod and shutdown illegal!\n");
		mutex_unlock(&fullstop_mutex);
		schedule_timeout_uninterruptible(10);
		return true;
	}
	WRITE_ONCE(fullstop, FULLSTOP_RMMOD);
	mutex_unlock(&fullstop_mutex);
	torture_shutdown_cleanup();
	torture_shuffle_cleanup();
	torture_stutter_cleanup();
	torture_onoff_cleanup();
	return false;
}
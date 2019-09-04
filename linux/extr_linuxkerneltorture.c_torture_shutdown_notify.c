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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ FULLSTOP_DONTSTOP ; 
 int /*<<< orphan*/  FULLSTOP_SHUTDOWN ; 
 int NOTIFY_DONE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fullstop ; 
 int /*<<< orphan*/  fullstop_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int torture_shutdown_notify(struct notifier_block *unused1,
				   unsigned long unused2, void *unused3)
{
	mutex_lock(&fullstop_mutex);
	if (READ_ONCE(fullstop) == FULLSTOP_DONTSTOP) {
		VERBOSE_TOROUT_STRING("Unscheduled system shutdown detected");
		WRITE_ONCE(fullstop, FULLSTOP_SHUTDOWN);
	} else {
		pr_warn("Concurrent rmmod and shutdown illegal!\n");
	}
	mutex_unlock(&fullstop_mutex);
	return NOTIFY_DONE;
}
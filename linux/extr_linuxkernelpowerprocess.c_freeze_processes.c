#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  PF_SUSPEND_TASK ; 
 int /*<<< orphan*/  UMH_DISABLED ; 
 int /*<<< orphan*/  UMH_FREEZING ; 
 int __usermodehelper_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __usermodehelper_set_disable_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  freeze_timeout_msecs ; 
 int /*<<< orphan*/  in_atomic () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oom_killer_disable (int /*<<< orphan*/ ) ; 
 int pm_freezing ; 
 int /*<<< orphan*/  pm_wakeup_clear (int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  system_freezing_cnt ; 
 int /*<<< orphan*/  thaw_processes () ; 
 int try_to_freeze_tasks (int) ; 

int freeze_processes(void)
{
	int error;

	error = __usermodehelper_disable(UMH_FREEZING);
	if (error)
		return error;

	/* Make sure this task doesn't get frozen */
	current->flags |= PF_SUSPEND_TASK;

	if (!pm_freezing)
		atomic_inc(&system_freezing_cnt);

	pm_wakeup_clear(true);
	pr_info("Freezing user space processes ... ");
	pm_freezing = true;
	error = try_to_freeze_tasks(true);
	if (!error) {
		__usermodehelper_set_disable_depth(UMH_DISABLED);
		pr_cont("done.");
	}
	pr_cont("\n");
	BUG_ON(in_atomic());

	/*
	 * Now that the whole userspace is frozen we need to disbale
	 * the OOM killer to disallow any further interference with
	 * killable tasks. There is no guarantee oom victims will
	 * ever reach a point they go away we have to wait with a timeout.
	 */
	if (!error && !oom_killer_disable(msecs_to_jiffies(freeze_timeout_msecs)))
		error = -EBUSY;

	if (error)
		thaw_processes();
	return error;
}
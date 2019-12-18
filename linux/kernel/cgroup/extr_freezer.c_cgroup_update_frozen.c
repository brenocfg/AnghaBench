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
struct TYPE_2__ {scalar_t__ nr_frozen_tasks; } ;
struct cgroup {int /*<<< orphan*/  events_file; int /*<<< orphan*/  flags; TYPE_1__ freezer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_FREEZE ; 
 int /*<<< orphan*/  CGRP_FROZEN ; 
 int /*<<< orphan*/  TRACE_CGROUP_PATH (int /*<<< orphan*/ ,struct cgroup*,int) ; 
 scalar_t__ __cgroup_task_count (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_file_notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_propagate_frozen (struct cgroup*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_frozen ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cgroup_update_frozen(struct cgroup *cgrp)
{
	bool frozen;

	lockdep_assert_held(&css_set_lock);

	/*
	 * If the cgroup has to be frozen (CGRP_FREEZE bit set),
	 * and all tasks are frozen and/or stopped, let's consider
	 * the cgroup frozen. Otherwise it's not frozen.
	 */
	frozen = test_bit(CGRP_FREEZE, &cgrp->flags) &&
		cgrp->freezer.nr_frozen_tasks == __cgroup_task_count(cgrp);

	if (frozen) {
		/* Already there? */
		if (test_bit(CGRP_FROZEN, &cgrp->flags))
			return;

		set_bit(CGRP_FROZEN, &cgrp->flags);
	} else {
		/* Already there? */
		if (!test_bit(CGRP_FROZEN, &cgrp->flags))
			return;

		clear_bit(CGRP_FROZEN, &cgrp->flags);
	}
	cgroup_file_notify(&cgrp->events_file);
	TRACE_CGROUP_PATH(notify_frozen, cgrp, frozen);

	/* Update the state of ancestor cgroups. */
	cgroup_propagate_frozen(cgrp, frozen);
}
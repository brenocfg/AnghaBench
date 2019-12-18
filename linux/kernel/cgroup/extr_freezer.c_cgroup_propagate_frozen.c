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
struct TYPE_2__ {scalar_t__ nr_frozen_descendants; } ;
struct cgroup {scalar_t__ nr_descendants; int /*<<< orphan*/  events_file; int /*<<< orphan*/  flags; TYPE_1__ freezer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_FREEZE ; 
 int /*<<< orphan*/  CGRP_FROZEN ; 
 int /*<<< orphan*/  TRACE_CGROUP_PATH (int /*<<< orphan*/ ,struct cgroup*,int) ; 
 int /*<<< orphan*/  cgroup_file_notify (int /*<<< orphan*/ *) ; 
 struct cgroup* cgroup_parent (struct cgroup*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_frozen ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_propagate_frozen(struct cgroup *cgrp, bool frozen)
{
	int desc = 1;

	/*
	 * If the new state is frozen, some freezing ancestor cgroups may change
	 * their state too, depending on if all their descendants are frozen.
	 *
	 * Otherwise, all ancestor cgroups are forced into the non-frozen state.
	 */
	while ((cgrp = cgroup_parent(cgrp))) {
		if (frozen) {
			cgrp->freezer.nr_frozen_descendants += desc;
			if (!test_bit(CGRP_FROZEN, &cgrp->flags) &&
			    test_bit(CGRP_FREEZE, &cgrp->flags) &&
			    cgrp->freezer.nr_frozen_descendants ==
			    cgrp->nr_descendants) {
				set_bit(CGRP_FROZEN, &cgrp->flags);
				cgroup_file_notify(&cgrp->events_file);
				TRACE_CGROUP_PATH(notify_frozen, cgrp, 1);
				desc++;
			}
		} else {
			cgrp->freezer.nr_frozen_descendants -= desc;
			if (test_bit(CGRP_FROZEN, &cgrp->flags)) {
				clear_bit(CGRP_FROZEN, &cgrp->flags);
				cgroup_file_notify(&cgrp->events_file);
				TRACE_CGROUP_PATH(notify_frozen, cgrp, 0);
				desc++;
			}
		}
	}
}
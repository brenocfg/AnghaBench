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
typedef  int /*<<< orphan*/  u16 ;
struct cgroup {TYPE_1__* root; int /*<<< orphan*/  subtree_ss_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsys_mask; } ;

/* Variables and functions */
 scalar_t__ cgroup_is_threaded (struct cgroup*) ; 
 struct cgroup* cgroup_parent (struct cgroup*) ; 
 int /*<<< orphan*/  cgrp_dfl_threaded_ss_mask ; 

__attribute__((used)) static u16 cgroup_ss_mask(struct cgroup *cgrp)
{
	struct cgroup *parent = cgroup_parent(cgrp);

	if (parent) {
		u16 ss_mask = parent->subtree_ss_mask;

		/* threaded cgroups can only have threaded controllers */
		if (cgroup_is_threaded(cgrp))
			ss_mask &= cgrp_dfl_threaded_ss_mask;
		return ss_mask;
	}

	return cgrp->root->subsys_mask;
}
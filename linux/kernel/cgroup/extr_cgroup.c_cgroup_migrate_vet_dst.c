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
struct cgroup {scalar_t__ subtree_control; int /*<<< orphan*/  dom_cgrp; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 scalar_t__ cgroup_can_be_thread_root (struct cgroup*) ; 
 scalar_t__ cgroup_is_mixable (struct cgroup*) ; 
 scalar_t__ cgroup_is_threaded (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_is_valid_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_on_dfl (struct cgroup*) ; 

int cgroup_migrate_vet_dst(struct cgroup *dst_cgrp)
{
	/* v1 doesn't have any restriction */
	if (!cgroup_on_dfl(dst_cgrp))
		return 0;

	/* verify @dst_cgrp can host resources */
	if (!cgroup_is_valid_domain(dst_cgrp->dom_cgrp))
		return -EOPNOTSUPP;

	/* mixables don't care */
	if (cgroup_is_mixable(dst_cgrp))
		return 0;

	/*
	 * If @dst_cgrp is already or can become a thread root or is
	 * threaded, it doesn't matter.
	 */
	if (cgroup_can_be_thread_root(dst_cgrp) || cgroup_is_threaded(dst_cgrp))
		return 0;

	/* apply no-internal-process constraint */
	if (dst_cgrp->subtree_control)
		return -EBUSY;

	return 0;
}
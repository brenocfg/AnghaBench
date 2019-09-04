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
struct kernfs_node {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_CGROUP_PATH (int /*<<< orphan*/ ,struct cgroup*) ; 
 int cgroup_destroy_locked (struct cgroup*) ; 
 struct cgroup* cgroup_kn_lock_live (struct kernfs_node*,int) ; 
 int /*<<< orphan*/  cgroup_kn_unlock (struct kernfs_node*) ; 
 int /*<<< orphan*/  rmdir ; 

int cgroup_rmdir(struct kernfs_node *kn)
{
	struct cgroup *cgrp;
	int ret = 0;

	cgrp = cgroup_kn_lock_live(kn, false);
	if (!cgrp)
		return 0;

	ret = cgroup_destroy_locked(cgrp);
	if (!ret)
		TRACE_CGROUP_PATH(rmdir, cgrp);

	cgroup_kn_unlock(kn);
	return ret;
}
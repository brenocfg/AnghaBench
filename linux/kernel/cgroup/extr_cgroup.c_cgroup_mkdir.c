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
typedef  int /*<<< orphan*/  umode_t ;
struct kernfs_node {int /*<<< orphan*/  self; struct kernfs_node* kn; } ;
struct cgroup {int /*<<< orphan*/  self; struct cgroup* kn; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct kernfs_node*) ; 
 int PTR_ERR (struct kernfs_node*) ; 
 int /*<<< orphan*/  TRACE_CGROUP_PATH (int /*<<< orphan*/ ,struct kernfs_node*) ; 
 int cgroup_apply_control_enable (struct kernfs_node*) ; 
 int /*<<< orphan*/  cgroup_check_hierarchy_limits (struct kernfs_node*) ; 
 struct kernfs_node* cgroup_create (struct kernfs_node*) ; 
 int /*<<< orphan*/  cgroup_destroy_locked (struct kernfs_node*) ; 
 struct kernfs_node* cgroup_kn_lock_live (struct kernfs_node*,int) ; 
 int cgroup_kn_set_ugid (struct kernfs_node*) ; 
 int /*<<< orphan*/  cgroup_kn_unlock (struct kernfs_node*) ; 
 int css_populate_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_activate (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_create_dir (struct kernfs_node*,char const*,int /*<<< orphan*/ ,struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  mkdir ; 
 scalar_t__ strchr (char const*,char) ; 

int cgroup_mkdir(struct kernfs_node *parent_kn, const char *name, umode_t mode)
{
	struct cgroup *parent, *cgrp;
	struct kernfs_node *kn;
	int ret;

	/* do not accept '\n' to prevent making /proc/<pid>/cgroup unparsable */
	if (strchr(name, '\n'))
		return -EINVAL;

	parent = cgroup_kn_lock_live(parent_kn, false);
	if (!parent)
		return -ENODEV;

	if (!cgroup_check_hierarchy_limits(parent)) {
		ret = -EAGAIN;
		goto out_unlock;
	}

	cgrp = cgroup_create(parent);
	if (IS_ERR(cgrp)) {
		ret = PTR_ERR(cgrp);
		goto out_unlock;
	}

	/* create the directory */
	kn = kernfs_create_dir(parent->kn, name, mode, cgrp);
	if (IS_ERR(kn)) {
		ret = PTR_ERR(kn);
		goto out_destroy;
	}
	cgrp->kn = kn;

	/*
	 * This extra ref will be put in cgroup_free_fn() and guarantees
	 * that @cgrp->kn is always accessible.
	 */
	kernfs_get(kn);

	ret = cgroup_kn_set_ugid(kn);
	if (ret)
		goto out_destroy;

	ret = css_populate_dir(&cgrp->self);
	if (ret)
		goto out_destroy;

	ret = cgroup_apply_control_enable(cgrp);
	if (ret)
		goto out_destroy;

	TRACE_CGROUP_PATH(mkdir, cgrp);

	/* let's create and online css's */
	kernfs_activate(kn);

	ret = 0;
	goto out_unlock;

out_destroy:
	cgroup_destroy_locked(cgrp);
out_unlock:
	cgroup_kn_unlock(parent_kn);
	return ret;
}
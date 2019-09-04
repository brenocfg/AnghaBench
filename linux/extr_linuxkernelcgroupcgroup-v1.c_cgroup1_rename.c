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
struct kernfs_node {struct kernfs_node* parent; struct cgroup* priv; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOTDIR ; 
 scalar_t__ KERNFS_DIR ; 
 int /*<<< orphan*/  TRACE_CGROUP_PATH (int /*<<< orphan*/ ,struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  kernfs_break_active_protection (struct kernfs_node*) ; 
 int kernfs_rename (struct kernfs_node*,struct kernfs_node*,char const*) ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_unbreak_active_protection (struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rename ; 

__attribute__((used)) static int cgroup1_rename(struct kernfs_node *kn, struct kernfs_node *new_parent,
			  const char *new_name_str)
{
	struct cgroup *cgrp = kn->priv;
	int ret;

	if (kernfs_type(kn) != KERNFS_DIR)
		return -ENOTDIR;
	if (kn->parent != new_parent)
		return -EIO;

	/*
	 * We're gonna grab cgroup_mutex which nests outside kernfs
	 * active_ref.  kernfs_rename() doesn't require active_ref
	 * protection.  Break them before grabbing cgroup_mutex.
	 */
	kernfs_break_active_protection(new_parent);
	kernfs_break_active_protection(kn);

	mutex_lock(&cgroup_mutex);

	ret = kernfs_rename(kn, new_parent, new_name_str);
	if (!ret)
		TRACE_CGROUP_PATH(rename, cgrp);

	mutex_unlock(&cgroup_mutex);

	kernfs_unbreak_active_protection(kn);
	kernfs_unbreak_active_protection(new_parent);
	return ret;
}
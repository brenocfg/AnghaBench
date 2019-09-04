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
struct super_block {int dummy; } ;
struct file_system_type {int dummy; } ;
struct dentry {struct super_block* d_sb; } ;
struct cgroup_root {int /*<<< orphan*/  cgrp; int /*<<< orphan*/  kf_root; } ;
struct cgroup_namespace {int /*<<< orphan*/  root_cset; } ;
struct cgroup {int /*<<< orphan*/  kn; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  cgroup_put (int /*<<< orphan*/ *) ; 
 struct cgroup* cset_cgroup_from_root (int /*<<< orphan*/ ,struct cgroup_root*) ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct cgroup_namespace init_cgroup_ns ; 
 struct dentry* kernfs_mount (struct file_system_type*,int,int /*<<< orphan*/ ,unsigned long,int*) ; 
 struct dentry* kernfs_node_dentry (int /*<<< orphan*/ ,struct super_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

struct dentry *cgroup_do_mount(struct file_system_type *fs_type, int flags,
			       struct cgroup_root *root, unsigned long magic,
			       struct cgroup_namespace *ns)
{
	struct dentry *dentry;
	bool new_sb = false;

	dentry = kernfs_mount(fs_type, flags, root->kf_root, magic, &new_sb);

	/*
	 * In non-init cgroup namespace, instead of root cgroup's dentry,
	 * we return the dentry corresponding to the cgroupns->root_cgrp.
	 */
	if (!IS_ERR(dentry) && ns != &init_cgroup_ns) {
		struct dentry *nsdentry;
		struct super_block *sb = dentry->d_sb;
		struct cgroup *cgrp;

		mutex_lock(&cgroup_mutex);
		spin_lock_irq(&css_set_lock);

		cgrp = cset_cgroup_from_root(ns->root_cset, root);

		spin_unlock_irq(&css_set_lock);
		mutex_unlock(&cgroup_mutex);

		nsdentry = kernfs_node_dentry(cgrp->kn, sb);
		dput(dentry);
		if (IS_ERR(nsdentry))
			deactivate_locked_super(sb);
		dentry = nsdentry;
	}

	if (!new_sb)
		cgroup_put(&root->cgrp);

	return dentry;
}
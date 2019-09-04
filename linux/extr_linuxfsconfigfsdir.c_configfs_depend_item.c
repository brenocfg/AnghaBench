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
struct dentry {int /*<<< orphan*/  d_fsdata; } ;
struct config_item {int dummy; } ;
struct TYPE_2__ {struct config_item cg_item; } ;
struct configfs_subsystem {TYPE_1__ su_group; } ;
struct configfs_dirent {int /*<<< orphan*/  s_dentry; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int configfs_do_depend_item (int /*<<< orphan*/ ,struct config_item*) ; 
 struct configfs_dirent* configfs_find_subsys_dentry (int /*<<< orphan*/ ,struct config_item*) ; 
 struct dentry* configfs_pin_fs () ; 
 int /*<<< orphan*/  configfs_release_fs () ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 

int configfs_depend_item(struct configfs_subsystem *subsys,
			 struct config_item *target)
{
	int ret;
	struct configfs_dirent *subsys_sd;
	struct config_item *s_item = &subsys->su_group.cg_item;
	struct dentry *root;

	/*
	 * Pin the configfs filesystem.  This means we can safely access
	 * the root of the configfs filesystem.
	 */
	root = configfs_pin_fs();
	if (IS_ERR(root))
		return PTR_ERR(root);

	/*
	 * Next, lock the root directory.  We're going to check that the
	 * subsystem is really registered, and so we need to lock out
	 * configfs_[un]register_subsystem().
	 */
	inode_lock(d_inode(root));

	subsys_sd = configfs_find_subsys_dentry(root->d_fsdata, s_item);
	if (!subsys_sd) {
		ret = -ENOENT;
		goto out_unlock_fs;
	}

	/* Ok, now we can trust subsys/s_item */
	ret = configfs_do_depend_item(subsys_sd->s_dentry, target);

out_unlock_fs:
	inode_unlock(d_inode(root));

	/*
	 * If we succeeded, the fs is pinned via other methods.  If not,
	 * we're done with it anyway.  So release_fs() is always right.
	 */
	configfs_release_fs();

	return ret;
}
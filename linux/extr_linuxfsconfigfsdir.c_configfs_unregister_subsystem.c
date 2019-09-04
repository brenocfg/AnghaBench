#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dentry {struct dentry* d_parent; TYPE_1__* d_sb; } ;
struct TYPE_8__ {struct dentry* ci_dentry; } ;
struct config_group {TYPE_5__ cg_item; } ;
struct configfs_subsystem {struct config_group su_group; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_flags; } ;
struct TYPE_6__ {struct dentry* s_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  configfs_detach_group (TYPE_5__*) ; 
 scalar_t__ configfs_detach_prep (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  configfs_release_fs () ; 
 int /*<<< orphan*/  configfs_symlink_mutex ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 TYPE_2__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dont_mount (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_group (struct config_group*) ; 

void configfs_unregister_subsystem(struct configfs_subsystem *subsys)
{
	struct config_group *group = &subsys->su_group;
	struct dentry *dentry = group->cg_item.ci_dentry;
	struct dentry *root = dentry->d_sb->s_root;

	if (dentry->d_parent != root) {
		pr_err("Tried to unregister non-subsystem!\n");
		return;
	}

	inode_lock_nested(d_inode(root),
			  I_MUTEX_PARENT);
	inode_lock_nested(d_inode(dentry), I_MUTEX_CHILD);
	mutex_lock(&configfs_symlink_mutex);
	spin_lock(&configfs_dirent_lock);
	if (configfs_detach_prep(dentry, NULL)) {
		pr_err("Tried to unregister non-empty subsystem!\n");
	}
	spin_unlock(&configfs_dirent_lock);
	mutex_unlock(&configfs_symlink_mutex);
	configfs_detach_group(&group->cg_item);
	d_inode(dentry)->i_flags |= S_DEAD;
	dont_mount(dentry);
	inode_unlock(d_inode(dentry));

	d_delete(dentry);

	inode_unlock(d_inode(root));

	dput(dentry);

	unlink_group(group);
	configfs_release_fs();
}
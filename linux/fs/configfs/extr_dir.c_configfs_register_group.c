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
struct configfs_subsystem {int /*<<< orphan*/  su_mutex; } ;
struct configfs_fragment {int dummy; } ;
struct TYPE_2__ {struct dentry* ci_dentry; } ;
struct config_group {TYPE_1__ cg_item; struct configfs_subsystem* cg_subsys; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  configfs_dir_set_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int create_default_group (struct config_group*,struct config_group*,struct configfs_fragment*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_group (struct config_group*,struct config_group*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct configfs_fragment* new_fragment () ; 
 int /*<<< orphan*/  put_fragment (struct configfs_fragment*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_group (struct config_group*) ; 

int configfs_register_group(struct config_group *parent_group,
			    struct config_group *group)
{
	struct configfs_subsystem *subsys = parent_group->cg_subsys;
	struct dentry *parent;
	struct configfs_fragment *frag;
	int ret;

	frag = new_fragment();
	if (!frag)
		return -ENOMEM;

	mutex_lock(&subsys->su_mutex);
	link_group(parent_group, group);
	mutex_unlock(&subsys->su_mutex);

	parent = parent_group->cg_item.ci_dentry;

	inode_lock_nested(d_inode(parent), I_MUTEX_PARENT);
	ret = create_default_group(parent_group, group, frag);
	if (ret)
		goto err_out;

	spin_lock(&configfs_dirent_lock);
	configfs_dir_set_ready(group->cg_item.ci_dentry->d_fsdata);
	spin_unlock(&configfs_dirent_lock);
	inode_unlock(d_inode(parent));
	put_fragment(frag);
	return 0;
err_out:
	inode_unlock(d_inode(parent));
	mutex_lock(&subsys->su_mutex);
	unlink_group(group);
	mutex_unlock(&subsys->su_mutex);
	put_fragment(frag);
	return ret;
}
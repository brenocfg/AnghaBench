#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {struct configfs_dirent* d_fsdata; } ;
struct configfs_fragment {int dummy; } ;
struct configfs_dirent {int /*<<< orphan*/  s_type; } ;
struct config_item {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGFS_USET_DIR ; 
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  configfs_adjust_dir_dirent_depth_after_populate (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_adjust_dir_dirent_depth_before_populate (struct configfs_dirent*) ; 
 int configfs_attach_item (struct config_item*,struct config_item*,struct dentry*,struct configfs_fragment*) ; 
 int /*<<< orphan*/  configfs_detach_item (struct config_item*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dont_mount (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_1__*) ; 
 int populate_groups (int /*<<< orphan*/ ,struct configfs_fragment*) ; 
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 

__attribute__((used)) static int configfs_attach_group(struct config_item *parent_item,
				 struct config_item *item,
				 struct dentry *dentry,
				 struct configfs_fragment *frag)
{
	int ret;
	struct configfs_dirent *sd;

	ret = configfs_attach_item(parent_item, item, dentry, frag);
	if (!ret) {
		sd = dentry->d_fsdata;
		sd->s_type |= CONFIGFS_USET_DIR;

		/*
		 * FYI, we're faking mkdir in populate_groups()
		 * We must lock the group's inode to avoid races with the VFS
		 * which can already hit the inode and try to add/remove entries
		 * under it.
		 *
		 * We must also lock the inode to remove it safely in case of
		 * error, as rmdir() would.
		 */
		inode_lock_nested(d_inode(dentry), I_MUTEX_CHILD);
		configfs_adjust_dir_dirent_depth_before_populate(sd);
		ret = populate_groups(to_config_group(item), frag);
		if (ret) {
			configfs_detach_item(item);
			d_inode(dentry)->i_flags |= S_DEAD;
			dont_mount(dentry);
		}
		configfs_adjust_dir_dirent_depth_after_populate(sd);
		inode_unlock(d_inode(dentry));
		if (ret)
			d_delete(dentry);
	}

	return ret;
}
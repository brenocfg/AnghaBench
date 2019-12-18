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
struct dentry {int dummy; } ;
struct configfs_fragment {int dummy; } ;
struct config_item {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_DEAD ; 
 int configfs_create_dir (struct config_item*,struct dentry*,struct configfs_fragment*) ; 
 int /*<<< orphan*/  configfs_remove_dir (struct config_item*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dont_mount (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_1__*) ; 
 int populate_attrs (struct config_item*) ; 

__attribute__((used)) static int configfs_attach_item(struct config_item *parent_item,
				struct config_item *item,
				struct dentry *dentry,
				struct configfs_fragment *frag)
{
	int ret;

	ret = configfs_create_dir(item, dentry, frag);
	if (!ret) {
		ret = populate_attrs(item);
		if (ret) {
			/*
			 * We are going to remove an inode and its dentry but
			 * the VFS may already have hit and used them. Thus,
			 * we must lock them as rmdir() would.
			 */
			inode_lock(d_inode(dentry));
			configfs_remove_dir(item);
			d_inode(dentry)->i_flags |= S_DEAD;
			dont_mount(dentry);
			inode_unlock(d_inode(dentry));
			d_delete(dentry);
		}
	}

	return ret;
}
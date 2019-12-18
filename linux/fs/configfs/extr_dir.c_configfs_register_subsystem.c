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
struct dentry {struct configfs_dirent* d_fsdata; } ;
struct TYPE_2__ {scalar_t__ ci_name; scalar_t__ ci_namebuf; } ;
struct config_group {TYPE_1__ cg_item; } ;
struct configfs_subsystem {struct config_group su_group; } ;
struct configfs_fragment {int dummy; } ;
struct configfs_dirent {int /*<<< orphan*/  s_element; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 int configfs_attach_group (int /*<<< orphan*/ ,TYPE_1__*,struct dentry*,struct configfs_fragment*) ; 
 int /*<<< orphan*/  configfs_dir_set_ready (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 struct dentry* configfs_pin_fs () ; 
 int /*<<< orphan*/  configfs_release_fs () ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_alloc_name (struct dentry*,scalar_t__) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_group (int /*<<< orphan*/ ,struct config_group*) ; 
 struct configfs_fragment* new_fragment () ; 
 int /*<<< orphan*/  put_fragment (struct configfs_fragment*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_config_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_group (struct config_group*) ; 

int configfs_register_subsystem(struct configfs_subsystem *subsys)
{
	int err;
	struct config_group *group = &subsys->su_group;
	struct dentry *dentry;
	struct dentry *root;
	struct configfs_dirent *sd;
	struct configfs_fragment *frag;

	frag = new_fragment();
	if (!frag)
		return -ENOMEM;

	root = configfs_pin_fs();
	if (IS_ERR(root)) {
		put_fragment(frag);
		return PTR_ERR(root);
	}

	if (!group->cg_item.ci_name)
		group->cg_item.ci_name = group->cg_item.ci_namebuf;

	sd = root->d_fsdata;
	link_group(to_config_group(sd->s_element), group);

	inode_lock_nested(d_inode(root), I_MUTEX_PARENT);

	err = -ENOMEM;
	dentry = d_alloc_name(root, group->cg_item.ci_name);
	if (dentry) {
		d_add(dentry, NULL);

		err = configfs_attach_group(sd->s_element, &group->cg_item,
					    dentry, frag);
		if (err) {
			BUG_ON(d_inode(dentry));
			d_drop(dentry);
			dput(dentry);
		} else {
			spin_lock(&configfs_dirent_lock);
			configfs_dir_set_ready(dentry->d_fsdata);
			spin_unlock(&configfs_dirent_lock);
		}
	}

	inode_unlock(d_inode(root));

	if (err) {
		unlink_group(group);
		configfs_release_fs();
	}
	put_fragment(frag);

	return err;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct path {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; TYPE_2__* d_parent; } ;
struct configfs_dirent {int dummy; } ;
struct config_item_type {TYPE_1__* ct_item_ops; } ;
struct config_item {struct config_item_type* ci_type; } ;
struct TYPE_4__ {struct configfs_dirent* d_fsdata; } ;
struct TYPE_3__ {int (* allow_link ) (struct config_item*,struct config_item*) ;int /*<<< orphan*/  (* drop_link ) (struct config_item*,struct config_item*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  configfs_dirent_is_ready (struct configfs_dirent*) ; 
 struct config_item* configfs_get_config_item (TYPE_2__*) ; 
 int /*<<< orphan*/  configfs_symlink_mutex ; 
 int create_link (struct config_item*,struct config_item*,struct dentry*) ; 
 int get_target (char const*,struct path*,struct config_item**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int stub1 (struct config_item*,struct config_item*) ; 
 int /*<<< orphan*/  stub2 (struct config_item*,struct config_item*) ; 

int configfs_symlink(struct inode *dir, struct dentry *dentry, const char *symname)
{
	int ret;
	struct path path;
	struct configfs_dirent *sd;
	struct config_item *parent_item;
	struct config_item *target_item = NULL;
	const struct config_item_type *type;

	sd = dentry->d_parent->d_fsdata;
	/*
	 * Fake invisibility if dir belongs to a group/default groups hierarchy
	 * being attached
	 */
	ret = -ENOENT;
	if (!configfs_dirent_is_ready(sd))
		goto out;

	parent_item = configfs_get_config_item(dentry->d_parent);
	type = parent_item->ci_type;

	ret = -EPERM;
	if (!type || !type->ct_item_ops ||
	    !type->ct_item_ops->allow_link)
		goto out_put;

	ret = get_target(symname, &path, &target_item, dentry->d_sb);
	if (ret)
		goto out_put;

	ret = type->ct_item_ops->allow_link(parent_item, target_item);
	if (!ret) {
		mutex_lock(&configfs_symlink_mutex);
		ret = create_link(parent_item, target_item, dentry);
		mutex_unlock(&configfs_symlink_mutex);
		if (ret && type->ct_item_ops->drop_link)
			type->ct_item_ops->drop_link(parent_item,
						     target_item);
	}

	config_item_put(target_item);
	path_put(&path);

out_put:
	config_item_put(parent_item);

out:
	return ret;
}
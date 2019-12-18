#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {struct dentry* d_parent; struct configfs_dirent* d_fsdata; } ;
struct TYPE_8__ {TYPE_1__* ci_type; } ;
struct TYPE_9__ {TYPE_2__ cg_item; } ;
struct configfs_subsystem {int /*<<< orphan*/  su_mutex; TYPE_3__ su_group; } ;
struct configfs_fragment {int frag_dead; int /*<<< orphan*/  frag_sem; } ;
struct configfs_dirent {int s_type; struct configfs_fragment* s_frag; scalar_t__ s_dependent_count; } ;
struct config_item {TYPE_4__* ci_type; } ;
struct TYPE_11__ {struct configfs_subsystem* cg_subsys; } ;
struct TYPE_10__ {struct module* ct_owner; } ;
struct TYPE_7__ {struct module* ct_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CONFIGFS_USET_DEFAULT ; 
 int CONFIGFS_USET_DIR ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  client_disconnect_notify (struct config_item*,struct config_item*) ; 
 int /*<<< orphan*/  client_drop_item (struct config_item*,struct config_item*) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  configfs_detach_group (struct config_item*) ; 
 int /*<<< orphan*/  configfs_detach_item (struct config_item*) ; 
 int configfs_detach_prep (struct dentry*,struct dentry**) ; 
 int /*<<< orphan*/  configfs_detach_rollback (struct dentry*) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 struct config_item* configfs_get_config_item (struct dentry*) ; 
 int /*<<< orphan*/  configfs_symlink_mutex ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ down_write_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_5__* to_config_group (struct config_item*) ; 
 int /*<<< orphan*/  unlink_group (TYPE_5__*) ; 
 int /*<<< orphan*/  unlink_obj (struct config_item*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int configfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct config_item *parent_item;
	struct config_item *item;
	struct configfs_subsystem *subsys;
	struct configfs_dirent *sd;
	struct configfs_fragment *frag;
	struct module *subsys_owner = NULL, *dead_item_owner = NULL;
	int ret;

	sd = dentry->d_fsdata;
	if (sd->s_type & CONFIGFS_USET_DEFAULT)
		return -EPERM;

	/* Get a working ref until we have the child */
	parent_item = configfs_get_config_item(dentry->d_parent);
	subsys = to_config_group(parent_item)->cg_subsys;
	BUG_ON(!subsys);

	if (!parent_item->ci_type) {
		config_item_put(parent_item);
		return -EINVAL;
	}

	/* configfs_mkdir() shouldn't have allowed this */
	BUG_ON(!subsys->su_group.cg_item.ci_type);
	subsys_owner = subsys->su_group.cg_item.ci_type->ct_owner;

	/*
	 * Ensure that no racing symlink() will make detach_prep() fail while
	 * the new link is temporarily attached
	 */
	do {
		struct dentry *wait;

		mutex_lock(&configfs_symlink_mutex);
		spin_lock(&configfs_dirent_lock);
		/*
		 * Here's where we check for dependents.  We're protected by
		 * configfs_dirent_lock.
		 * If no dependent, atomically tag the item as dropping.
		 */
		ret = sd->s_dependent_count ? -EBUSY : 0;
		if (!ret) {
			ret = configfs_detach_prep(dentry, &wait);
			if (ret)
				configfs_detach_rollback(dentry);
		}
		spin_unlock(&configfs_dirent_lock);
		mutex_unlock(&configfs_symlink_mutex);

		if (ret) {
			if (ret != -EAGAIN) {
				config_item_put(parent_item);
				return ret;
			}

			/* Wait until the racing operation terminates */
			inode_lock(d_inode(wait));
			inode_unlock(d_inode(wait));
			dput(wait);
		}
	} while (ret == -EAGAIN);

	frag = sd->s_frag;
	if (down_write_killable(&frag->frag_sem)) {
		spin_lock(&configfs_dirent_lock);
		configfs_detach_rollback(dentry);
		spin_unlock(&configfs_dirent_lock);
		return -EINTR;
	}
	frag->frag_dead = true;
	up_write(&frag->frag_sem);

	/* Get a working ref for the duration of this function */
	item = configfs_get_config_item(dentry);

	/* Drop reference from above, item already holds one. */
	config_item_put(parent_item);

	if (item->ci_type)
		dead_item_owner = item->ci_type->ct_owner;

	if (sd->s_type & CONFIGFS_USET_DIR) {
		configfs_detach_group(item);

		mutex_lock(&subsys->su_mutex);
		client_disconnect_notify(parent_item, item);
		unlink_group(to_config_group(item));
	} else {
		configfs_detach_item(item);

		mutex_lock(&subsys->su_mutex);
		client_disconnect_notify(parent_item, item);
		unlink_obj(item);
	}

	client_drop_item(parent_item, item);
	mutex_unlock(&subsys->su_mutex);

	/* Drop our reference from above */
	config_item_put(item);

	module_put(dead_item_owner);
	module_put(subsys_owner);

	return 0;
}
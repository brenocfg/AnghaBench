#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dentry {struct configfs_dirent* d_fsdata; } ;
struct configfs_subsystem {int /*<<< orphan*/  su_mutex; } ;
struct configfs_fragment {int frag_dead; int /*<<< orphan*/  frag_sem; } ;
struct configfs_dirent {struct configfs_fragment* s_frag; } ;
struct TYPE_9__ {TYPE_1__* ci_parent; struct dentry* ci_dentry; } ;
struct config_group {TYPE_6__ cg_item; struct configfs_subsystem* cg_subsys; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_flags; } ;
struct TYPE_7__ {struct dentry* ci_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  configfs_detach_group (TYPE_6__*) ; 
 int /*<<< orphan*/  configfs_detach_prep (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 TYPE_2__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dont_mount (struct dentry*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_rmdir (TYPE_2__*,struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_group (struct config_group*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void configfs_unregister_group(struct config_group *group)
{
	struct configfs_subsystem *subsys = group->cg_subsys;
	struct dentry *dentry = group->cg_item.ci_dentry;
	struct dentry *parent = group->cg_item.ci_parent->ci_dentry;
	struct configfs_dirent *sd = dentry->d_fsdata;
	struct configfs_fragment *frag = sd->s_frag;

	down_write(&frag->frag_sem);
	frag->frag_dead = true;
	up_write(&frag->frag_sem);

	inode_lock_nested(d_inode(parent), I_MUTEX_PARENT);
	spin_lock(&configfs_dirent_lock);
	configfs_detach_prep(dentry, NULL);
	spin_unlock(&configfs_dirent_lock);

	configfs_detach_group(&group->cg_item);
	d_inode(dentry)->i_flags |= S_DEAD;
	dont_mount(dentry);
	fsnotify_rmdir(d_inode(parent), dentry);
	d_delete(dentry);
	inode_unlock(d_inode(parent));

	dput(dentry);

	mutex_lock(&subsys->su_mutex);
	unlink_group(group);
	mutex_unlock(&subsys->su_mutex);
}
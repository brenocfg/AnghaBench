#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_op; } ;
struct dentry {TYPE_2__* d_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_flags; } ;
struct TYPE_4__ {int (* rmdir ) (struct inode*,struct dentry*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  detach_mounts (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dont_mount (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_rmdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_2__*) ; 
 scalar_t__ is_local_mountpoint (struct dentry*) ; 
 int may_delete (struct inode*,struct dentry*,int) ; 
 int security_inode_rmdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*) ; 

int vfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	int error = may_delete(dir, dentry, 1);

	if (error)
		return error;

	if (!dir->i_op->rmdir)
		return -EPERM;

	dget(dentry);
	inode_lock(dentry->d_inode);

	error = -EBUSY;
	if (is_local_mountpoint(dentry))
		goto out;

	error = security_inode_rmdir(dir, dentry);
	if (error)
		goto out;

	error = dir->i_op->rmdir(dir, dentry);
	if (error)
		goto out;

	shrink_dcache_parent(dentry);
	dentry->d_inode->i_flags |= S_DEAD;
	dont_mount(dentry);
	detach_mounts(dentry);
	fsnotify_rmdir(dir, dentry);

out:
	inode_unlock(dentry->d_inode);
	dput(dentry);
	if (!error)
		d_delete(dentry);
	return error;
}
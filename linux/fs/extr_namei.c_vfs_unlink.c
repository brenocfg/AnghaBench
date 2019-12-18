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
struct inode {TYPE_1__* i_op; } ;
struct dentry {int d_flags; struct inode* d_inode; } ;
struct TYPE_2__ {int (* unlink ) (struct inode*,struct dentry*) ;} ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  detach_mounts (struct dentry*) ; 
 int /*<<< orphan*/  dont_mount (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_link_count (struct inode*) ; 
 int /*<<< orphan*/  fsnotify_unlink (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ is_local_mountpoint (struct dentry*) ; 
 int may_delete (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int security_inode_unlink (struct inode*,struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*) ; 
 int try_break_deleg (struct inode*,struct inode**) ; 

int vfs_unlink(struct inode *dir, struct dentry *dentry, struct inode **delegated_inode)
{
	struct inode *target = dentry->d_inode;
	int error = may_delete(dir, dentry, 0);

	if (error)
		return error;

	if (!dir->i_op->unlink)
		return -EPERM;

	inode_lock(target);
	if (is_local_mountpoint(dentry))
		error = -EBUSY;
	else {
		error = security_inode_unlink(dir, dentry);
		if (!error) {
			error = try_break_deleg(target, delegated_inode);
			if (error)
				goto out;
			error = dir->i_op->unlink(dir, dentry);
			if (!error) {
				dont_mount(dentry);
				detach_mounts(dentry);
				fsnotify_unlink(dir, dentry);
			}
		}
	}
out:
	inode_unlock(target);

	/* We don't d_delete() NFS sillyrenamed files--they still exist. */
	if (!error && !(dentry->d_flags & DCACHE_NFSFS_RENAMED)) {
		fsnotify_link_count(target);
		d_delete(dentry);
	}

	return error;
}
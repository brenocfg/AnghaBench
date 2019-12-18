#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vfsmount {int dummy; } ;
struct path {struct dentry* dentry; struct vfsmount* mnt; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  ovl_cleanup (struct inode*,struct dentry*) ; 
 int ovl_do_rmdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  ovl_workdir_cleanup_recurse (struct path*,int) ; 

void ovl_workdir_cleanup(struct inode *dir, struct vfsmount *mnt,
			 struct dentry *dentry, int level)
{
	int err;

	if (!d_is_dir(dentry) || level > 1) {
		ovl_cleanup(dir, dentry);
		return;
	}

	err = ovl_do_rmdir(dir, dentry);
	if (err) {
		struct path path = { .mnt = mnt, .dentry = dentry };

		inode_unlock(dir);
		ovl_workdir_cleanup_recurse(&path, level + 1);
		inode_lock_nested(dir, I_MUTEX_PARENT);
		ovl_cleanup(dir, dentry);
	}
}
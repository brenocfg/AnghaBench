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
struct inode {int dummy; } ;
struct dentry {int d_flags; struct dentry* d_parent; } ;
struct TYPE_2__ {int (* remove ) (struct inode*,struct dentry*) ;} ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 int EBUSY ; 
 int ENOENT ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  VFS ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct dentry*) ; 
 int /*<<< orphan*/  nfs_dentry_handle_enoent (struct dentry*) ; 
 int /*<<< orphan*/  nfs_drop_nlink (struct inode*) ; 
 int stub1 (struct inode*,struct dentry*) ; 
 int stub2 (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  trace_nfs_remove_enter (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  trace_nfs_remove_exit (struct inode*,struct dentry*,int) ; 

__attribute__((used)) static int nfs_safe_remove(struct dentry *dentry)
{
	struct inode *dir = d_inode(dentry->d_parent);
	struct inode *inode = d_inode(dentry);
	int error = -EBUSY;
		
	dfprintk(VFS, "NFS: safe_remove(%pd2)\n", dentry);

	/* If the dentry was sillyrenamed, we simply call d_delete() */
	if (dentry->d_flags & DCACHE_NFSFS_RENAMED) {
		error = 0;
		goto out;
	}

	trace_nfs_remove_enter(dir, dentry);
	if (inode != NULL) {
		error = NFS_PROTO(dir)->remove(dir, dentry);
		if (error == 0)
			nfs_drop_nlink(inode);
	} else
		error = NFS_PROTO(dir)->remove(dir, dentry);
	if (error == -ENOENT)
		nfs_dentry_handle_enoent(dentry);
	trace_nfs_remove_exit(dir, dentry, error);
out:
	return error;
}
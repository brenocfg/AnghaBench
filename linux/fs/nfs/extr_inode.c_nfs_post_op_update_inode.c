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
struct nfs_fattr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int NFS_INO_INVALID_CHANGE ; 
 int NFS_INO_INVALID_CTIME ; 
 int NFS_INO_REVAL_FORCED ; 
 int /*<<< orphan*/  nfs_fattr_set_barrier (struct nfs_fattr*) ; 
 int nfs_post_op_update_inode_locked (struct inode*,struct nfs_fattr*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int nfs_post_op_update_inode(struct inode *inode, struct nfs_fattr *fattr)
{
	int status;

	spin_lock(&inode->i_lock);
	nfs_fattr_set_barrier(fattr);
	status = nfs_post_op_update_inode_locked(inode, fattr,
			NFS_INO_INVALID_CHANGE
			| NFS_INO_INVALID_CTIME
			| NFS_INO_REVAL_FORCED);
	spin_unlock(&inode->i_lock);

	return status;
}
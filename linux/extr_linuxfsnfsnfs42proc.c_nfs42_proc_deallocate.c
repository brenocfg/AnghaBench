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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t NFSPROC4_CLNT_DEALLOCATE ; 
 int /*<<< orphan*/  NFS_CAP_DEALLOCATE ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int nfs42_proc_fallocate (struct rpc_message*,struct file*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_server_capable (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_sync_inode (struct inode*) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,scalar_t__,scalar_t__) ; 

int nfs42_proc_deallocate(struct file *filep, loff_t offset, loff_t len)
{
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_DEALLOCATE],
	};
	struct inode *inode = file_inode(filep);
	int err;

	if (!nfs_server_capable(inode, NFS_CAP_DEALLOCATE))
		return -EOPNOTSUPP;

	inode_lock(inode);
	err = nfs_sync_inode(inode);
	if (err)
		goto out_unlock;

	err = nfs42_proc_fallocate(&msg, filep, offset, len);
	if (err == 0)
		truncate_pagecache_range(inode, offset, (offset + len) -1);
	if (err == -EOPNOTSUPP)
		NFS_SERVER(inode)->caps &= ~NFS_CAP_DEALLOCATE;
out_unlock:
	inode_unlock(inode);
	return err;
}
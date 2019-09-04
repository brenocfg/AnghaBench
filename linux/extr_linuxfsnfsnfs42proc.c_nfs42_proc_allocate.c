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
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t NFSPROC4_CLNT_ALLOCATE ; 
 int /*<<< orphan*/  NFS_CAP_ALLOCATE ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int nfs42_proc_fallocate (struct rpc_message*,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_server_capable (struct inode*,int /*<<< orphan*/ ) ; 

int nfs42_proc_allocate(struct file *filep, loff_t offset, loff_t len)
{
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_ALLOCATE],
	};
	struct inode *inode = file_inode(filep);
	int err;

	if (!nfs_server_capable(inode, NFS_CAP_ALLOCATE))
		return -EOPNOTSUPP;

	inode_lock(inode);

	err = nfs42_proc_fallocate(&msg, filep, offset, len);
	if (err == -EOPNOTSUPP)
		NFS_SERVER(inode)->caps &= ~NFS_CAP_ALLOCATE;

	inode_unlock(inode);
	return err;
}
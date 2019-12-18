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
struct rpc_task {int dummy; } ;
struct nfs_lock_context {int /*<<< orphan*/  io_count; TYPE_1__* open_context; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  uoc_rpcwaitq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task (int /*<<< orphan*/ *,struct rpc_task*) ; 

bool
nfs_async_iocounter_wait(struct rpc_task *task, struct nfs_lock_context *l_ctx)
{
	struct inode *inode = d_inode(l_ctx->open_context->dentry);
	bool ret = false;

	if (atomic_read(&l_ctx->io_count) > 0) {
		rpc_sleep_on(&NFS_SERVER(inode)->uoc_rpcwaitq, task, NULL);
		ret = true;
	}

	if (atomic_read(&l_ctx->io_count) == 0) {
		rpc_wake_up_queued_task(&NFS_SERVER(inode)->uoc_rpcwaitq, task);
		ret = false;
	}

	return ret;
}
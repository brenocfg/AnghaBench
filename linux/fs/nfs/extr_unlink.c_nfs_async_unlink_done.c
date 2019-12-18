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
struct rpc_task {int /*<<< orphan*/  tk_status; } ;
struct nfs_unlinkdata {TYPE_1__* dentry; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* unlink_done ) (struct rpc_task*,struct inode*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*,struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_sillyrename_unlink (struct nfs_unlinkdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_async_unlink_done(struct rpc_task *task, void *calldata)
{
	struct nfs_unlinkdata *data = calldata;
	struct inode *dir = d_inode(data->dentry->d_parent);

	trace_nfs_sillyrename_unlink(data, task->tk_status);
	if (!NFS_PROTO(dir)->unlink_done(task, dir))
		rpc_restart_call_prepare(task);
}
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
struct TYPE_4__ {int /*<<< orphan*/  stateid; TYPE_1__* context; } ;
struct nfs_pgio_header {int /*<<< orphan*/  timestamp; TYPE_2__ args; struct inode* inode; } ;
struct nfs4_exception {scalar_t__ retry; int /*<<< orphan*/ * stateid; int /*<<< orphan*/  state; struct inode* inode; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs4_async_handle_exception (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs4_exception*) ; 
 int /*<<< orphan*/  nfs_writeback_update_inode (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  renew_lease (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 
 int /*<<< orphan*/  trace_nfs4_write (struct nfs_pgio_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_write_done_cb(struct rpc_task *task,
			      struct nfs_pgio_header *hdr)
{
	struct inode *inode = hdr->inode;

	trace_nfs4_write(hdr, task->tk_status);
	if (task->tk_status < 0) {
		struct nfs4_exception exception = {
			.inode = hdr->inode,
			.state = hdr->args.context->state,
			.stateid = &hdr->args.stateid,
		};
		task->tk_status = nfs4_async_handle_exception(task,
				NFS_SERVER(inode), task->tk_status,
				&exception);
		if (exception.retry) {
			rpc_restart_call_prepare(task);
			return -EAGAIN;
		}
	}
	if (task->tk_status >= 0) {
		renew_lease(NFS_SERVER(inode), hdr->timestamp);
		nfs_writeback_update_inode(hdr);
	}
	return 0;
}
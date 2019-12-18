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
struct rpc_task {scalar_t__ tk_status; struct nfs_unlinkdata* tk_calldata; } ;
struct nfs_removeres {TYPE_1__* dir_attr; int /*<<< orphan*/  cinfo; int /*<<< orphan*/  server; int /*<<< orphan*/  seq_res; } ;
struct nfs_unlinkdata {int /*<<< orphan*/  timeout; struct nfs_removeres res; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  time_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  nfs4_async_handle_error (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_sequence_done (struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_changeattr (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_proc_unlink_done(struct rpc_task *task, struct inode *dir)
{
	struct nfs_unlinkdata *data = task->tk_calldata;
	struct nfs_removeres *res = &data->res;

	if (!nfs4_sequence_done(task, &res->seq_res))
		return 0;
	if (nfs4_async_handle_error(task, res->server, NULL,
				    &data->timeout) == -EAGAIN)
		return 0;
	if (task->tk_status == 0)
		update_changeattr(dir, &res->cinfo,
				res->dir_attr->time_start, 0);
	return 1;
}
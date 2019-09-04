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
struct rpc_task {scalar_t__ tk_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  osr_seq_res; } ;
struct nfs42_offloadcancel_data {int /*<<< orphan*/  seq_server; TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  nfs41_sequence_done (struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_async_handle_error (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 

__attribute__((used)) static void nfs42_offload_cancel_done(struct rpc_task *task, void *calldata)
{
	struct nfs42_offloadcancel_data *data = calldata;

	nfs41_sequence_done(task, &data->res.osr_seq_res);
	if (task->tk_status &&
		nfs4_async_handle_error(task, data->seq_server, NULL,
			NULL) == -EAGAIN)
		rpc_restart_call_prepare(task);
}
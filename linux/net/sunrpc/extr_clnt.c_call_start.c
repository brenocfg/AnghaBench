#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* rpc_proc; } ;
struct rpc_task {int /*<<< orphan*/  tk_action; int /*<<< orphan*/  tk_pid; TYPE_2__ tk_msg; struct rpc_clnt* tk_client; } ;
struct rpc_clnt {size_t cl_vers; TYPE_5__* cl_stats; TYPE_4__* cl_program; } ;
struct TYPE_10__ {int /*<<< orphan*/  rpccnt; } ;
struct TYPE_9__ {TYPE_3__** version; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/ * counts; } ;
struct TYPE_6__ {int p_statidx; } ;

/* Variables and functions */
 scalar_t__ RPC_IS_ASYNC (struct rpc_task*) ; 
 int /*<<< orphan*/  call_reserve ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rpc_proc_name (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_task_set_transport (struct rpc_task*,struct rpc_clnt*) ; 
 int /*<<< orphan*/  trace_rpc_request (struct rpc_task*) ; 

__attribute__((used)) static void
call_start(struct rpc_task *task)
{
	struct rpc_clnt	*clnt = task->tk_client;
	int idx = task->tk_msg.rpc_proc->p_statidx;

	trace_rpc_request(task);
	dprintk("RPC: %5u call_start %s%d proc %s (%s)\n", task->tk_pid,
			clnt->cl_program->name, clnt->cl_vers,
			rpc_proc_name(task),
			(RPC_IS_ASYNC(task) ? "async" : "sync"));

	/* Increment call count (version might not be valid for ping) */
	if (clnt->cl_program->version[clnt->cl_vers])
		clnt->cl_program->version[clnt->cl_vers]->counts[idx]++;
	clnt->cl_stats->rpccnt++;
	task->tk_action = call_reserve;
	rpc_task_set_transport(task, clnt);
}
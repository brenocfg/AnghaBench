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
struct rpc_task {unsigned short tk_flags; int /*<<< orphan*/  tk_pid; int /*<<< orphan*/  tk_calldata; int /*<<< orphan*/  tk_ops; int /*<<< orphan*/  tk_op_cred; } ;

/* Variables and functions */
 unsigned short RPC_TASK_DYNAMIC ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_release_calldata (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_task_mempool ; 

__attribute__((used)) static void rpc_free_task(struct rpc_task *task)
{
	unsigned short tk_flags = task->tk_flags;

	put_rpccred(task->tk_op_cred);
	rpc_release_calldata(task->tk_ops, task->tk_calldata);

	if (tk_flags & RPC_TASK_DYNAMIC) {
		dprintk("RPC: %5u freeing task\n", task->tk_pid);
		mempool_free(task, rpc_task_mempool);
	}
}
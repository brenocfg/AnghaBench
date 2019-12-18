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
struct rpc_task {int /*<<< orphan*/  tk_task; int /*<<< orphan*/  tk_flags; struct rpc_clnt* tk_client; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_tasks; int /*<<< orphan*/  cl_swapper; scalar_t__ cl_noretranstimeo; scalar_t__ cl_softerr; scalar_t__ cl_softrtry; int /*<<< orphan*/  cl_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_NO_RETRANS_TIMEOUT ; 
 int /*<<< orphan*/  RPC_TASK_SOFT ; 
 int /*<<< orphan*/  RPC_TASK_SWAPPER ; 
 int /*<<< orphan*/  RPC_TASK_TIMEOUT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_task_set_transport (struct rpc_task*,struct rpc_clnt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void rpc_task_set_client(struct rpc_task *task, struct rpc_clnt *clnt)
{

	if (clnt != NULL) {
		rpc_task_set_transport(task, clnt);
		task->tk_client = clnt;
		atomic_inc(&clnt->cl_count);
		if (clnt->cl_softrtry)
			task->tk_flags |= RPC_TASK_SOFT;
		if (clnt->cl_softerr)
			task->tk_flags |= RPC_TASK_TIMEOUT;
		if (clnt->cl_noretranstimeo)
			task->tk_flags |= RPC_TASK_NO_RETRANS_TIMEOUT;
		if (atomic_read(&clnt->cl_swapper))
			task->tk_flags |= RPC_TASK_SWAPPER;
		/* Add to the client's list of all tasks */
		spin_lock(&clnt->cl_lock);
		list_add_tail(&task->tk_task, &clnt->cl_tasks);
		spin_unlock(&clnt->cl_lock);
	}
}
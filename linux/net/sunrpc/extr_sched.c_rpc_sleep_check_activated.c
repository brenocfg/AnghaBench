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
struct rpc_task {int /*<<< orphan*/  tk_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  RPC_IS_ACTIVATED (struct rpc_task*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  rpc_put_task_async (struct rpc_task*) ; 

__attribute__((used)) static bool rpc_sleep_check_activated(struct rpc_task *task)
{
	/* We shouldn't ever put an inactive task to sleep */
	if (WARN_ON_ONCE(!RPC_IS_ACTIVATED(task))) {
		task->tk_status = -EIO;
		rpc_put_task_async(task);
		return false;
	}
	return true;
}
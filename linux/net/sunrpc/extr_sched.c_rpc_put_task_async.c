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
struct rpc_task {int /*<<< orphan*/  tk_workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_do_put_task (struct rpc_task*,int /*<<< orphan*/ ) ; 

void rpc_put_task_async(struct rpc_task *task)
{
	rpc_do_put_task(task, task->tk_workqueue);
}
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
struct TYPE_2__ {int /*<<< orphan*/ * rpc_cred; } ;
struct rpc_task {TYPE_1__ tk_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_task_release_client (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_release (struct rpc_task*) ; 

__attribute__((used)) static void rpc_release_resources_task(struct rpc_task *task)
{
	xprt_release(task);
	if (task->tk_msg.rpc_cred) {
		put_cred(task->tk_msg.rpc_cred);
		task->tk_msg.rpc_cred = NULL;
	}
	rpc_task_release_client(task);
}
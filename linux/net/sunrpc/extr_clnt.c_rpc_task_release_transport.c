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
struct rpc_xprt {int dummy; } ;
struct rpc_task {scalar_t__ tk_client; struct rpc_xprt* tk_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_task_release_xprt (scalar_t__,struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_put (struct rpc_xprt*) ; 

void rpc_task_release_transport(struct rpc_task *task)
{
	struct rpc_xprt *xprt = task->tk_xprt;

	if (xprt) {
		task->tk_xprt = NULL;
		if (task->tk_client)
			rpc_task_release_xprt(task->tk_client, xprt);
		else
			xprt_put(xprt);
	}
}
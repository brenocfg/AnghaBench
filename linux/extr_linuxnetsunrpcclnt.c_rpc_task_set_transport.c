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
struct rpc_task {scalar_t__ tk_xprt; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_xpi; } ;

/* Variables and functions */
 scalar_t__ xprt_iter_get_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void rpc_task_set_transport(struct rpc_task *task, struct rpc_clnt *clnt)
{
	if (!task->tk_xprt)
		task->tk_xprt = xprt_iter_get_next(&clnt->cl_xpi);
}
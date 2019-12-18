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
struct rpc_xprt {TYPE_1__* ops; } ;
struct rpc_task {int /*<<< orphan*/ * tk_rqstp; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* alloc_slot ) (struct rpc_xprt*,struct rpc_task*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_request_init (struct rpc_task*) ; 

__attribute__((used)) static void
xprt_do_reserve(struct rpc_xprt *xprt, struct rpc_task *task)
{
	xprt->ops->alloc_slot(xprt, task);
	if (task->tk_rqstp != NULL)
		xprt_request_init(task);
}
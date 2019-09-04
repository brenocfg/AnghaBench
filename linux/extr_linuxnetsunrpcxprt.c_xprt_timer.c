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
struct rpc_task {int /*<<< orphan*/  tk_status; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_reply_bytes_recvd; int /*<<< orphan*/  rq_xid; struct rpc_xprt* rq_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* timer ) (struct rpc_xprt*,struct rpc_task*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,struct rpc_task*) ; 
 int /*<<< orphan*/  trace_xprt_timer (struct rpc_xprt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xprt_timer(struct rpc_task *task)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_xprt *xprt = req->rq_xprt;

	if (task->tk_status != -ETIMEDOUT)
		return;

	trace_xprt_timer(xprt, req->rq_xid, task->tk_status);
	if (!req->rq_reply_bytes_recvd) {
		if (xprt->ops->timer)
			xprt->ops->timer(xprt, task);
	} else
		task->tk_status = 0;
}
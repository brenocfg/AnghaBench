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
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {scalar_t__ rq_connect_cookie; struct rpc_xprt* rq_xprt; } ;

/* Variables and functions */
 scalar_t__ xprt_connect_cookie (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_connected (struct rpc_xprt*) ; 

__attribute__((used)) static bool
xprt_request_retransmit_after_disconnect(struct rpc_task *task)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_xprt *xprt = req->rq_xprt;

	return req->rq_connect_cookie != xprt_connect_cookie(xprt) ||
		!xprt_connected(xprt);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* rpc_proc; } ;
struct rpc_task {struct rpc_rqst* tk_rqstp; struct rpc_clnt* tk_client; TYPE_4__ tk_msg; } ;
struct rpc_rtt {int dummy; } ;
struct rpc_rqst {unsigned long rq_retries; TYPE_2__* rq_xprt; } ;
struct rpc_clnt {TYPE_1__* cl_timeout; struct rpc_rtt* cl_rtt; } ;
struct TYPE_7__ {int p_timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  pending; } ;
struct TYPE_5__ {unsigned long to_maxval; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 unsigned long rpc_calc_rto (struct rpc_rtt*,int) ; 
 unsigned long rpc_ntimeo (struct rpc_rtt*,int) ; 
 int /*<<< orphan*/  rpc_sleep_on_timeout (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xprt_timer ; 

void xprt_wait_for_reply_request_rtt(struct rpc_task *task)
{
	int timer = task->tk_msg.rpc_proc->p_timer;
	struct rpc_clnt *clnt = task->tk_client;
	struct rpc_rtt *rtt = clnt->cl_rtt;
	struct rpc_rqst *req = task->tk_rqstp;
	unsigned long max_timeout = clnt->cl_timeout->to_maxval;
	unsigned long timeout;

	timeout = rpc_calc_rto(rtt, timer);
	timeout <<= rpc_ntimeo(rtt, timer) + req->rq_retries;
	if (timeout > max_timeout || timeout == 0)
		timeout = max_timeout;
	rpc_sleep_on_timeout(&req->rq_xprt->pending, task, xprt_timer,
			jiffies + timeout);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* rpc_proc; } ;
struct rpc_task {TYPE_3__ tk_msg; TYPE_1__* tk_client; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rtt {int dummy; } ;
struct rpc_rqst {int rq_ntrans; int /*<<< orphan*/  rq_rtt; } ;
struct TYPE_5__ {unsigned int p_timer; } ;
struct TYPE_4__ {struct rpc_rtt* cl_rtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_set_timeo (struct rpc_rtt*,unsigned int,int) ; 
 int /*<<< orphan*/  rpc_update_rtt (struct rpc_rtt*,unsigned int,long) ; 
 long usecs_to_jiffies (int /*<<< orphan*/ ) ; 

void xprt_update_rtt(struct rpc_task *task)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_rtt *rtt = task->tk_client->cl_rtt;
	unsigned int timer = task->tk_msg.rpc_proc->p_timer;
	long m = usecs_to_jiffies(ktime_to_us(req->rq_rtt));

	if (timer) {
		if (req->rq_ntrans == 1)
			rpc_update_rtt(rtt, timer, m);
		rpc_set_timeo(rtt, timer, req->rq_ntrans - 1);
	}
}
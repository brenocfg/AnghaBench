#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_xprt {int dummy; } ;
struct rpc_task {TYPE_2__* tk_client; int /*<<< orphan*/  tk_start; } ;
struct rpc_rqst {scalar_t__ rq_majortimeo; int /*<<< orphan*/  rq_timeout; struct rpc_xprt* rq_xprt; } ;
struct TYPE_4__ {TYPE_1__* cl_timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  to_initval; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 scalar_t__ likely (int) ; 
 unsigned long xprt_abs_ktime_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ xprt_calc_majortimeo (struct rpc_rqst*) ; 
 scalar_t__ xprt_connected (struct rpc_xprt*) ; 

__attribute__((used)) static void xprt_init_majortimeo(struct rpc_task *task, struct rpc_rqst *req)
{
	unsigned long time_init;
	struct rpc_xprt *xprt = req->rq_xprt;

	if (likely(xprt && xprt_connected(xprt)))
		time_init = jiffies;
	else
		time_init = xprt_abs_ktime_to_jiffies(task->tk_start);
	req->rq_timeout = task->tk_client->cl_timeout->to_initval;
	req->rq_majortimeo = time_init + xprt_calc_majortimeo(req);
}
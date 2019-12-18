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
struct rpc_timeout {unsigned long to_retries; unsigned long to_increment; unsigned long to_maxval; scalar_t__ to_exponential; } ;
struct rpc_rqst {unsigned long rq_timeout; TYPE_2__* rq_task; } ;
struct TYPE_4__ {TYPE_1__* tk_client; } ;
struct TYPE_3__ {struct rpc_timeout* cl_timeout; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long xprt_calc_majortimeo(struct rpc_rqst *req)
{
	const struct rpc_timeout *to = req->rq_task->tk_client->cl_timeout;
	unsigned long majortimeo = req->rq_timeout;

	if (to->to_exponential)
		majortimeo <<= to->to_retries;
	else
		majortimeo += to->to_increment * to->to_retries;
	if (majortimeo > to->to_maxval || majortimeo == 0)
		majortimeo = to->to_maxval;
	return majortimeo;
}
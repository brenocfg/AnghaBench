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
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {scalar_t__ rq_bytes_sent; } ;

/* Variables and functions */

__attribute__((used)) static void xprt_task_clear_bytes_sent(struct rpc_task *task)
{
	if (task != NULL) {
		struct rpc_rqst *req = task->tk_rqstp;
		if (req != NULL)
			req->rq_bytes_sent = 0;
	}
}
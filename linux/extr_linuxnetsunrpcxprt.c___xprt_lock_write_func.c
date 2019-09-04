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
struct rpc_xprt {struct rpc_task* snd_task; } ;
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_ntrans; } ;

/* Variables and functions */

__attribute__((used)) static bool __xprt_lock_write_func(struct rpc_task *task, void *data)
{
	struct rpc_xprt *xprt = data;
	struct rpc_rqst *req;

	req = task->tk_rqstp;
	xprt->snd_task = task;
	if (req)
		req->rq_ntrans++;
	return true;
}
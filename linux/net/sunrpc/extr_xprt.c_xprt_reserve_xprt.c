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
struct rpc_xprt {int /*<<< orphan*/  sending; struct rpc_task* snd_task; int /*<<< orphan*/  state; } ;
struct rpc_task {int /*<<< orphan*/  tk_status; int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ RPC_IS_SOFT (struct rpc_task*) ; 
 int /*<<< orphan*/  XPRT_LOCKED ; 
 int /*<<< orphan*/  XPRT_WRITE_SPACE ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct rpc_xprt*) ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_sleep_on_timeout (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_clear_locked (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_request_timeout (struct rpc_rqst*) ; 

int xprt_reserve_xprt(struct rpc_xprt *xprt, struct rpc_task *task)
{
	struct rpc_rqst *req = task->tk_rqstp;

	if (test_and_set_bit(XPRT_LOCKED, &xprt->state)) {
		if (task == xprt->snd_task)
			return 1;
		goto out_sleep;
	}
	if (test_bit(XPRT_WRITE_SPACE, &xprt->state))
		goto out_unlock;
	xprt->snd_task = task;

	return 1;

out_unlock:
	xprt_clear_locked(xprt);
out_sleep:
	dprintk("RPC: %5u failed to lock transport %p\n",
			task->tk_pid, xprt);
	task->tk_status = -EAGAIN;
	if  (RPC_IS_SOFT(task))
		rpc_sleep_on_timeout(&xprt->sending, task, NULL,
				xprt_request_timeout(req));
	else
		rpc_sleep_on(&xprt->sending, task, NULL);
	return 0;
}
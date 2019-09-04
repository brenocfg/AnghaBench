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
struct svc_xprt {int /*<<< orphan*/  xpt_mutex; int /*<<< orphan*/  xpt_flags; int /*<<< orphan*/  xpt_bc_pending; } ;
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {TYPE_1__* rq_xprt; int /*<<< orphan*/  rq_xid; } ;
struct TYPE_2__ {struct svc_xprt* bc_xprt; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  XPT_DEAD ; 
 int bc_sendto (struct rpc_rqst*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task (int /*<<< orphan*/ *,struct rpc_task*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bc_send_request(struct rpc_task *task)
{
	struct rpc_rqst *req = task->tk_rqstp;
	struct svc_xprt	*xprt;
	int len;

	dprintk("sending request with xid: %08x\n", ntohl(req->rq_xid));
	/*
	 * Get the server socket associated with this callback xprt
	 */
	xprt = req->rq_xprt->bc_xprt;

	/*
	 * Grab the mutex to serialize data as the connection is shared
	 * with the fore channel
	 */
	if (!mutex_trylock(&xprt->xpt_mutex)) {
		rpc_sleep_on(&xprt->xpt_bc_pending, task, NULL);
		if (!mutex_trylock(&xprt->xpt_mutex))
			return -EAGAIN;
		rpc_wake_up_queued_task(&xprt->xpt_bc_pending, task);
	}
	if (test_bit(XPT_DEAD, &xprt->xpt_flags))
		len = -ENOTCONN;
	else
		len = bc_sendto(req);
	mutex_unlock(&xprt->xpt_mutex);

	if (len > 0)
		len = 0;

	return len;
}
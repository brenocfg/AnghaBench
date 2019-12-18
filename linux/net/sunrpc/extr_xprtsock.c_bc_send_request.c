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
struct svc_xprt {int /*<<< orphan*/  xpt_mutex; int /*<<< orphan*/  xpt_flags; } ;
struct rpc_rqst {TYPE_1__* rq_xprt; int /*<<< orphan*/  rq_xid; } ;
struct TYPE_2__ {struct svc_xprt* bc_xprt; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  XPT_DEAD ; 
 int bc_sendto (struct rpc_rqst*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bc_send_request(struct rpc_rqst *req)
{
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
	mutex_lock(&xprt->xpt_mutex);
	if (test_bit(XPT_DEAD, &xprt->xpt_flags))
		len = -ENOTCONN;
	else
		len = bc_sendto(req);
	mutex_unlock(&xprt->xpt_mutex);

	if (len > 0)
		len = 0;

	return len;
}
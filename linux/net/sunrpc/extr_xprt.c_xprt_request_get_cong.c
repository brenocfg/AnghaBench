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
struct rpc_xprt {int /*<<< orphan*/  transport_lock; } ;
struct rpc_rqst {scalar_t__ rq_cong; } ;

/* Variables and functions */
 scalar_t__ __xprt_get_cong (struct rpc_xprt*,struct rpc_rqst*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool
xprt_request_get_cong(struct rpc_xprt *xprt, struct rpc_rqst *req)
{
	bool ret = false;

	if (req->rq_cong)
		return true;
	spin_lock(&xprt->transport_lock);
	ret = __xprt_get_cong(xprt, req) != 0;
	spin_unlock(&xprt->transport_lock);
	return ret;
}
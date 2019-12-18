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
struct rpc_xprt {int /*<<< orphan*/  reserve_lock; int /*<<< orphan*/  free; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rpc_rqst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_dynamic_free_slot (struct rpc_xprt*,struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_wake_up_backlog (struct rpc_xprt*) ; 

void xprt_free_slot(struct rpc_xprt *xprt, struct rpc_rqst *req)
{
	spin_lock(&xprt->reserve_lock);
	if (!xprt_dynamic_free_slot(xprt, req)) {
		memset(req, 0, sizeof(*req));	/* mark unused */
		list_add(&req->rq_list, &xprt->free);
	}
	xprt_wake_up_backlog(xprt);
	spin_unlock(&xprt->reserve_lock);
}
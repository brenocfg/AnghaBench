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
struct rpc_xprt {int /*<<< orphan*/  bc_pa_lock; int /*<<< orphan*/  bc_slot_count; int /*<<< orphan*/  bc_alloc_count; int /*<<< orphan*/  bc_pa_list; scalar_t__ connect_cookie; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_bc_pa_list; int /*<<< orphan*/  rq_bc_pa_state; scalar_t__ rq_connect_cookie; struct rpc_xprt* rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_BC_PA_IN_USE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_rqst*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_free_allocation (struct rpc_rqst*) ; 
 scalar_t__ xprt_need_to_requeue (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_put (struct rpc_xprt*) ; 

void xprt_free_bc_rqst(struct rpc_rqst *req)
{
	struct rpc_xprt *xprt = req->rq_xprt;

	dprintk("RPC:       free backchannel req=%p\n", req);

	req->rq_connect_cookie = xprt->connect_cookie - 1;
	smp_mb__before_atomic();
	clear_bit(RPC_BC_PA_IN_USE, &req->rq_bc_pa_state);
	smp_mb__after_atomic();

	/*
	 * Return it to the list of preallocations so that it
	 * may be reused by a new callback request.
	 */
	spin_lock_bh(&xprt->bc_pa_lock);
	if (xprt_need_to_requeue(xprt)) {
		list_add_tail(&req->rq_bc_pa_list, &xprt->bc_pa_list);
		xprt->bc_alloc_count++;
		atomic_inc(&xprt->bc_slot_count);
		req = NULL;
	}
	spin_unlock_bh(&xprt->bc_pa_lock);
	if (req != NULL) {
		/*
		 * The last remaining session was destroyed while this
		 * entry was in use.  Free the entry and don't attempt
		 * to add back to the list because there is no need to
		 * have anymore preallocated entries.
		 */
		dprintk("RPC:       Last session removed req=%p\n", req);
		xprt_free_allocation(req);
	}
	xprt_put(xprt);
}
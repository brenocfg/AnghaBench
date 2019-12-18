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
struct rpcrdma_ia {struct rdma_cm_id* ri_id; int /*<<< orphan*/  ri_pd; } ;
struct rpcrdma_xprt {int /*<<< orphan*/  rx_ep; struct rpcrdma_ia rx_ia; } ;
struct rdma_cm_id {scalar_t__ device; } ;
struct ib_qp_init_attr {int dummy; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 scalar_t__ IS_ERR (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int rdma_create_qp (struct rdma_cm_id*,int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  rdma_destroy_qp (struct rdma_cm_id*) ; 
 struct rdma_cm_id* rpcrdma_create_id (struct rpcrdma_xprt*,struct rpcrdma_ia*) ; 
 int /*<<< orphan*/  rpcrdma_ep_disconnect (int /*<<< orphan*/ *,struct rpcrdma_ia*) ; 
 int /*<<< orphan*/  trace_xprtrdma_reconnect (struct rpcrdma_xprt*) ; 

__attribute__((used)) static int rpcrdma_ep_reconnect(struct rpcrdma_xprt *r_xprt,
				struct ib_qp_init_attr *qp_init_attr)
{
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;
	struct rdma_cm_id *id, *old;
	int err, rc;

	trace_xprtrdma_reconnect(r_xprt);

	rpcrdma_ep_disconnect(&r_xprt->rx_ep, ia);

	rc = -EHOSTUNREACH;
	id = rpcrdma_create_id(r_xprt, ia);
	if (IS_ERR(id))
		goto out;

	/* As long as the new ID points to the same device as the
	 * old ID, we can reuse the transport's existing PD and all
	 * previously allocated MRs. Also, the same device means
	 * the transport's previous DMA mappings are still valid.
	 *
	 * This is a sanity check only. There should be no way these
	 * point to two different devices here.
	 */
	old = id;
	rc = -ENETUNREACH;
	if (ia->ri_id->device != id->device) {
		pr_err("rpcrdma: can't reconnect on different device!\n");
		goto out_destroy;
	}

	err = rdma_create_qp(id, ia->ri_pd, qp_init_attr);
	if (err)
		goto out_destroy;

	/* Atomically replace the transport's ID and QP. */
	rc = 0;
	old = ia->ri_id;
	ia->ri_id = id;
	rdma_destroy_qp(old);

out_destroy:
	rdma_destroy_id(old);
out:
	return rc;
}
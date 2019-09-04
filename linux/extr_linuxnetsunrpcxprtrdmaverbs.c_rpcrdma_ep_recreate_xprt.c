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
struct rpcrdma_xprt {int /*<<< orphan*/  rx_data; } ;
struct rpcrdma_ia {int /*<<< orphan*/  ri_pd; int /*<<< orphan*/  ri_id; } ;
struct rpcrdma_ep {int /*<<< orphan*/  rep_attr; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int rdma_create_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rpcrdma_ep_create (struct rpcrdma_ep*,struct rpcrdma_ia*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_ep_destroy (struct rpcrdma_ep*,struct rpcrdma_ia*) ; 
 int /*<<< orphan*/  rpcrdma_ia_close (struct rpcrdma_ia*) ; 
 scalar_t__ rpcrdma_ia_open (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  rpcrdma_mrs_create (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  trace_xprtrdma_reinsert (struct rpcrdma_xprt*) ; 

__attribute__((used)) static int
rpcrdma_ep_recreate_xprt(struct rpcrdma_xprt *r_xprt,
			 struct rpcrdma_ep *ep, struct rpcrdma_ia *ia)
{
	int rc, err;

	trace_xprtrdma_reinsert(r_xprt);

	rc = -EHOSTUNREACH;
	if (rpcrdma_ia_open(r_xprt))
		goto out1;

	rc = -ENOMEM;
	err = rpcrdma_ep_create(ep, ia, &r_xprt->rx_data);
	if (err) {
		pr_err("rpcrdma: rpcrdma_ep_create returned %d\n", err);
		goto out2;
	}

	rc = -ENETUNREACH;
	err = rdma_create_qp(ia->ri_id, ia->ri_pd, &ep->rep_attr);
	if (err) {
		pr_err("rpcrdma: rdma_create_qp returned %d\n", err);
		goto out3;
	}

	rpcrdma_mrs_create(r_xprt);
	return 0;

out3:
	rpcrdma_ep_destroy(ep, ia);
out2:
	rpcrdma_ia_close(ia);
out1:
	return rc;
}
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
struct svcxprt_rdma {int /*<<< orphan*/  sc_xprt; int /*<<< orphan*/  sc_qp; } ;
struct svc_rdma_recv_ctxt {int /*<<< orphan*/  rc_recv_wr; } ;

/* Variables and functions */
 int ib_post_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_rdma_recv_ctxt_put (struct svcxprt_rdma*,struct svc_rdma_recv_ctxt*) ; 
 int /*<<< orphan*/  svc_xprt_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_xprt_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_svcrdma_post_recv (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __svc_rdma_post_recv(struct svcxprt_rdma *rdma,
				struct svc_rdma_recv_ctxt *ctxt)
{
	int ret;

	svc_xprt_get(&rdma->sc_xprt);
	ret = ib_post_recv(rdma->sc_qp, &ctxt->rc_recv_wr, NULL);
	trace_svcrdma_post_recv(&ctxt->rc_recv_wr, ret);
	if (ret)
		goto err_post;
	return 0;

err_post:
	svc_rdma_recv_ctxt_put(rdma, ctxt);
	svc_xprt_put(&rdma->sc_xprt);
	return ret;
}
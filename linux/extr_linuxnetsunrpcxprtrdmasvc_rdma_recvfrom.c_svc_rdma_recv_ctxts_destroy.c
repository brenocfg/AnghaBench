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
struct svcxprt_rdma {int /*<<< orphan*/  sc_recv_ctxts; } ;
struct svc_rdma_recv_ctxt {int /*<<< orphan*/  rc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct svc_rdma_recv_ctxt* svc_rdma_next_recv_ctxt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_rdma_recv_ctxt_destroy (struct svcxprt_rdma*,struct svc_rdma_recv_ctxt*) ; 

void svc_rdma_recv_ctxts_destroy(struct svcxprt_rdma *rdma)
{
	struct svc_rdma_recv_ctxt *ctxt;

	while ((ctxt = svc_rdma_next_recv_ctxt(&rdma->sc_recv_ctxts))) {
		list_del(&ctxt->rc_list);
		svc_rdma_recv_ctxt_destroy(rdma, ctxt);
	}
}
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
struct svcxprt_rdma {int /*<<< orphan*/  sc_rw_ctxts; } ;
struct svc_rdma_rw_ctxt {int /*<<< orphan*/  rw_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct svc_rdma_rw_ctxt*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct svc_rdma_rw_ctxt* svc_rdma_next_ctxt (int /*<<< orphan*/ *) ; 

void svc_rdma_destroy_rw_ctxts(struct svcxprt_rdma *rdma)
{
	struct svc_rdma_rw_ctxt *ctxt;

	while ((ctxt = svc_rdma_next_ctxt(&rdma->sc_rw_ctxts)) != NULL) {
		list_del(&ctxt->rw_list);
		kfree(ctxt);
	}
}
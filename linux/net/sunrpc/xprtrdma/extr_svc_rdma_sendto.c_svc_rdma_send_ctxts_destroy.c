#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svcxprt_rdma {int /*<<< orphan*/  sc_max_req_size; TYPE_1__* sc_pd; int /*<<< orphan*/  sc_send_ctxts; } ;
struct svc_rdma_send_ctxt {struct svc_rdma_send_ctxt* sc_xprt_buf; TYPE_2__* sc_sges; int /*<<< orphan*/  sc_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct svc_rdma_send_ctxt*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct svc_rdma_send_ctxt* svc_rdma_next_send_ctxt (int /*<<< orphan*/ *) ; 

void svc_rdma_send_ctxts_destroy(struct svcxprt_rdma *rdma)
{
	struct svc_rdma_send_ctxt *ctxt;

	while ((ctxt = svc_rdma_next_send_ctxt(&rdma->sc_send_ctxts))) {
		list_del(&ctxt->sc_list);
		ib_dma_unmap_single(rdma->sc_pd->device,
				    ctxt->sc_sges[0].addr,
				    rdma->sc_max_req_size,
				    DMA_TO_DEVICE);
		kfree(ctxt->sc_xprt_buf);
		kfree(ctxt);
	}
}
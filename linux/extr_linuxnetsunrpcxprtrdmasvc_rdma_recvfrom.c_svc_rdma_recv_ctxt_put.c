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
struct svcxprt_rdma {int /*<<< orphan*/  sc_recv_lock; int /*<<< orphan*/  sc_recv_ctxts; } ;
struct svc_rdma_recv_ctxt {unsigned int rc_page_count; int /*<<< orphan*/  rc_list; int /*<<< orphan*/  rc_temp; int /*<<< orphan*/ * rc_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_rdma_recv_ctxt_destroy (struct svcxprt_rdma*,struct svc_rdma_recv_ctxt*) ; 

void svc_rdma_recv_ctxt_put(struct svcxprt_rdma *rdma,
			    struct svc_rdma_recv_ctxt *ctxt)
{
	unsigned int i;

	for (i = 0; i < ctxt->rc_page_count; i++)
		put_page(ctxt->rc_pages[i]);

	if (!ctxt->rc_temp) {
		spin_lock(&rdma->sc_recv_lock);
		list_add(&ctxt->rc_list, &rdma->sc_recv_ctxts);
		spin_unlock(&rdma->sc_recv_lock);
	} else
		svc_rdma_recv_ctxt_destroy(rdma, ctxt);
}
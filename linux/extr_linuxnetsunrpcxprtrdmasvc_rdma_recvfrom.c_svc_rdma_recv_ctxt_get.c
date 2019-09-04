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
struct svc_rdma_recv_ctxt {scalar_t__ rc_page_count; int /*<<< orphan*/  rc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct svc_rdma_recv_ctxt* svc_rdma_next_recv_ctxt (int /*<<< orphan*/ *) ; 
 struct svc_rdma_recv_ctxt* svc_rdma_recv_ctxt_alloc (struct svcxprt_rdma*) ; 

__attribute__((used)) static struct svc_rdma_recv_ctxt *
svc_rdma_recv_ctxt_get(struct svcxprt_rdma *rdma)
{
	struct svc_rdma_recv_ctxt *ctxt;

	spin_lock(&rdma->sc_recv_lock);
	ctxt = svc_rdma_next_recv_ctxt(&rdma->sc_recv_ctxts);
	if (!ctxt)
		goto out_empty;
	list_del(&ctxt->rc_list);
	spin_unlock(&rdma->sc_recv_lock);

out:
	ctxt->rc_page_count = 0;
	return ctxt;

out_empty:
	spin_unlock(&rdma->sc_recv_lock);

	ctxt = svc_rdma_recv_ctxt_alloc(rdma);
	if (!ctxt)
		return NULL;
	goto out;
}
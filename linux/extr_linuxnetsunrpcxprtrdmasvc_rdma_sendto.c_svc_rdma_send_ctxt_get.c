#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct svcxprt_rdma {int /*<<< orphan*/  sc_send_lock; int /*<<< orphan*/  sc_send_ctxts; } ;
struct TYPE_2__ {scalar_t__ num_sge; } ;
struct svc_rdma_send_ctxt {scalar_t__ sc_page_count; scalar_t__ sc_cur_sge_no; TYPE_1__ sc_send_wr; int /*<<< orphan*/  sc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct svc_rdma_send_ctxt* svc_rdma_next_send_ctxt (int /*<<< orphan*/ *) ; 
 struct svc_rdma_send_ctxt* svc_rdma_send_ctxt_alloc (struct svcxprt_rdma*) ; 

struct svc_rdma_send_ctxt *svc_rdma_send_ctxt_get(struct svcxprt_rdma *rdma)
{
	struct svc_rdma_send_ctxt *ctxt;

	spin_lock(&rdma->sc_send_lock);
	ctxt = svc_rdma_next_send_ctxt(&rdma->sc_send_ctxts);
	if (!ctxt)
		goto out_empty;
	list_del(&ctxt->sc_list);
	spin_unlock(&rdma->sc_send_lock);

out:
	ctxt->sc_send_wr.num_sge = 0;
	ctxt->sc_cur_sge_no = 0;
	ctxt->sc_page_count = 0;
	return ctxt;

out_empty:
	spin_unlock(&rdma->sc_send_lock);
	ctxt = svc_rdma_send_ctxt_alloc(rdma);
	if (!ctxt)
		return NULL;
	goto out;
}
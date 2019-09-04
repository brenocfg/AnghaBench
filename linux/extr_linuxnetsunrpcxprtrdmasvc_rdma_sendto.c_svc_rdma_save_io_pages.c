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
struct svc_rqst {int /*<<< orphan*/ ** rq_respages; int /*<<< orphan*/ ** rq_next_page; } ;
struct svc_rdma_send_ctxt {int sc_page_count; int /*<<< orphan*/ ** sc_pages; } ;

/* Variables and functions */

__attribute__((used)) static void svc_rdma_save_io_pages(struct svc_rqst *rqstp,
				   struct svc_rdma_send_ctxt *ctxt)
{
	int i, pages = rqstp->rq_next_page - rqstp->rq_respages;

	ctxt->sc_page_count += pages;
	for (i = 0; i < pages; i++) {
		ctxt->sc_pages[i] = rqstp->rq_respages[i];
		rqstp->rq_respages[i] = NULL;
	}

	/* Prevent svc_xprt_release from releasing pages in rq_pages */
	rqstp->rq_next_page = rqstp->rq_respages;
}
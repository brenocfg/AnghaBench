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
struct TYPE_3__ {int /*<<< orphan*/  buflen; int /*<<< orphan*/  len; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; int /*<<< orphan*/  page_len; int /*<<< orphan*/ * pages; } ;
struct svc_rqst {TYPE_1__ rq_arg; int /*<<< orphan*/ * rq_respages; int /*<<< orphan*/ * rq_next_page; int /*<<< orphan*/ * rq_pages; } ;
struct TYPE_4__ {int /*<<< orphan*/  buflen; int /*<<< orphan*/  len; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; int /*<<< orphan*/  page_len; } ;
struct svc_rdma_recv_ctxt {int rc_page_count; size_t rc_hdr_count; TYPE_2__ rc_arg; int /*<<< orphan*/ * rc_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rdma_read_complete(struct svc_rqst *rqstp,
			       struct svc_rdma_recv_ctxt *head)
{
	int page_no;

	/* Move Read chunk pages to rqstp so that they will be released
	 * when svc_process is done with them.
	 */
	for (page_no = 0; page_no < head->rc_page_count; page_no++) {
		put_page(rqstp->rq_pages[page_no]);
		rqstp->rq_pages[page_no] = head->rc_pages[page_no];
	}
	head->rc_page_count = 0;

	/* Point rq_arg.pages past header */
	rqstp->rq_arg.pages = &rqstp->rq_pages[head->rc_hdr_count];
	rqstp->rq_arg.page_len = head->rc_arg.page_len;

	/* rq_respages starts after the last arg page */
	rqstp->rq_respages = &rqstp->rq_pages[page_no];
	rqstp->rq_next_page = rqstp->rq_respages + 1;

	/* Rebuild rq_arg head and tail. */
	rqstp->rq_arg.head[0] = head->rc_arg.head[0];
	rqstp->rq_arg.tail[0] = head->rc_arg.tail[0];
	rqstp->rq_arg.len = head->rc_arg.len;
	rqstp->rq_arg.buflen = head->rc_arg.buflen;
}
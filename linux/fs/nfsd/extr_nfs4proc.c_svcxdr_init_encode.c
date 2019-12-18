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
struct TYPE_2__ {scalar_t__ iov_len; } ;
struct xdr_stream {int page_ptr; TYPE_1__ scratch; scalar_t__ end; scalar_t__ p; struct kvec* iov; struct xdr_buf* buf; } ;
struct xdr_buf {int pages; scalar_t__ buflen; struct kvec* head; scalar_t__ len; } ;
struct svc_rqst {int rq_page_end; scalar_t__ rq_auth_slack; struct xdr_buf rq_res; } ;
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
struct kvec {scalar_t__ iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 int PAGE_SIZE ; 

__attribute__((used)) static void svcxdr_init_encode(struct svc_rqst *rqstp,
			       struct nfsd4_compoundres *resp)
{
	struct xdr_stream *xdr = &resp->xdr;
	struct xdr_buf *buf = &rqstp->rq_res;
	struct kvec *head = buf->head;

	xdr->buf = buf;
	xdr->iov = head;
	xdr->p   = head->iov_base + head->iov_len;
	xdr->end = head->iov_base + PAGE_SIZE - rqstp->rq_auth_slack;
	/* Tail and page_len should be zero at this point: */
	buf->len = buf->head[0].iov_len;
	xdr->scratch.iov_len = 0;
	xdr->page_ptr = buf->pages - 1;
	buf->buflen = PAGE_SIZE * (1 + rqstp->rq_page_end - buf->pages)
		- rqstp->rq_auth_slack;
}
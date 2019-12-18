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
struct TYPE_3__ {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;
struct xdr_stream {struct rpc_rqst* rqst; int /*<<< orphan*/ * p; int /*<<< orphan*/  nwords; int /*<<< orphan*/ * end; TYPE_1__ scratch; struct xdr_buf* buf; } ;
struct xdr_buf {scalar_t__ page_len; int /*<<< orphan*/  len; TYPE_2__* head; } ;
struct rpc_rqst {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_QUADLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_set_iov (struct xdr_stream*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_set_page_base (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xdr_init_decode(struct xdr_stream *xdr, struct xdr_buf *buf, __be32 *p,
		     struct rpc_rqst *rqst)
{
	xdr->buf = buf;
	xdr->scratch.iov_base = NULL;
	xdr->scratch.iov_len = 0;
	xdr->nwords = XDR_QUADLEN(buf->len);
	if (buf->head[0].iov_len != 0)
		xdr_set_iov(xdr, buf->head, buf->len);
	else if (buf->page_len != 0)
		xdr_set_page_base(xdr, 0, buf->len);
	else
		xdr_set_iov(xdr, buf->head, buf->len);
	if (p != NULL && p > xdr->p && xdr->end >= p) {
		xdr->nwords -= p - xdr->p;
		xdr->p = p;
	}
	xdr->rqst = rqst;
}
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
struct xdr_stream {unsigned int nwords; struct xdr_buf* buf; } ;
struct xdr_buf {unsigned int len; unsigned int page_len; struct kvec* head; } ;
struct kvec {unsigned int iov_len; } ;

/* Variables and functions */
 void* XDR_QUADLEN (unsigned int) ; 
 int /*<<< orphan*/  trace_rpc_xdr_alignment (struct xdr_stream*,unsigned int,unsigned int) ; 
 unsigned int xdr_shrink_bufhead (struct xdr_buf*,unsigned int) ; 
 unsigned int xdr_shrink_pagelen (struct xdr_buf*,unsigned int) ; 
 unsigned int xdr_stream_pos (struct xdr_stream*) ; 

__attribute__((used)) static unsigned int xdr_align_pages(struct xdr_stream *xdr, unsigned int len)
{
	struct xdr_buf *buf = xdr->buf;
	struct kvec *iov;
	unsigned int nwords = XDR_QUADLEN(len);
	unsigned int cur = xdr_stream_pos(xdr);
	unsigned int copied, offset;

	if (xdr->nwords == 0)
		return 0;

	/* Realign pages to current pointer position */
	iov = buf->head;
	if (iov->iov_len > cur) {
		offset = iov->iov_len - cur;
		copied = xdr_shrink_bufhead(buf, offset);
		trace_rpc_xdr_alignment(xdr, offset, copied);
		xdr->nwords = XDR_QUADLEN(buf->len - cur);
	}

	if (nwords > xdr->nwords) {
		nwords = xdr->nwords;
		len = nwords << 2;
	}
	if (buf->page_len <= len)
		len = buf->page_len;
	else if (nwords < xdr->nwords) {
		/* Truncate page data and move it into the tail */
		offset = buf->page_len - len;
		copied = xdr_shrink_pagelen(buf, offset);
		trace_rpc_xdr_alignment(xdr, offset, copied);
		xdr->nwords = XDR_QUADLEN(buf->len - cur);
	}
	return len;
}
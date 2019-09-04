#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_buf {scalar_t__ len; scalar_t__ page_len; TYPE_2__* tail; TYPE_1__* head; } ;
struct svc_rqst {scalar_t__ rq_next_page; struct nfsd4_compoundres* rq_resp; } ;
struct TYPE_6__ {scalar_t__ page_ptr; struct xdr_buf* buf; } ;
struct nfsd4_compoundres {int /*<<< orphan*/  opcnt; int /*<<< orphan*/  taglen; int /*<<< orphan*/  tag; int /*<<< orphan*/ * tagp; TYPE_3__ xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {scalar_t__ iov_len; } ;
struct TYPE_4__ {scalar_t__ iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  XDR_QUADLEN (int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_sequence_done (struct nfsd4_compoundres*) ; 

int
nfs4svc_encode_compoundres(struct svc_rqst *rqstp, __be32 *p)
{
	/*
	 * All that remains is to write the tag and operation count...
	 */
	struct nfsd4_compoundres *resp = rqstp->rq_resp;
	struct xdr_buf *buf = resp->xdr.buf;

	WARN_ON_ONCE(buf->len != buf->head[0].iov_len + buf->page_len +
				 buf->tail[0].iov_len);

	rqstp->rq_next_page = resp->xdr.page_ptr + 1;

	p = resp->tagp;
	*p++ = htonl(resp->taglen);
	memcpy(p, resp->tag, resp->taglen);
	p += XDR_QUADLEN(resp->taglen);
	*p++ = htonl(resp->opcnt);

	nfsd4_sequence_done(resp);
	return 1;
}
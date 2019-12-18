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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct xdr_stream {int dummy; } ;
struct xdr_buf {int page_base; scalar_t__ len; scalar_t__ buflen; struct kvec* head; struct kvec* tail; scalar_t__ page_len; struct page** pages; } ;
struct rpc_task {struct rpc_rqst* tk_rqstp; } ;
struct rpc_rqst {scalar_t__ rq_seqno; int rq_enc_pages_num; struct page** rq_enc_pages; struct xdr_buf rq_snd_buf; } ;
struct rpc_cred {int /*<<< orphan*/  cr_flags; } ;
struct page {int dummy; } ;
struct kvec {int iov_len; char* iov_base; } ;
struct gss_cl_ctx {int /*<<< orphan*/  gc_gss_ctx; } ;
typedef  char __be32 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  RPCAUTH_CRED_UPTODATE ; 
 int alloc_enc_pages (struct rpc_rqst*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char cpu_to_be32 (scalar_t__) ; 
 scalar_t__ gss_wrap (int /*<<< orphan*/ ,scalar_t__,struct xdr_buf*,struct page**) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* page_address (struct page*) ; 
 scalar_t__ rpcauth_wrap_req_encode (struct rpc_task*,struct xdr_stream*) ; 
 int /*<<< orphan*/  trace_rpcgss_wrap (struct rpc_task*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 char* xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static int gss_wrap_req_priv(struct rpc_cred *cred, struct gss_cl_ctx *ctx,
			     struct rpc_task *task, struct xdr_stream *xdr)
{
	struct rpc_rqst *rqstp = task->tk_rqstp;
	struct xdr_buf	*snd_buf = &rqstp->rq_snd_buf;
	u32		pad, offset, maj_stat;
	int		status;
	__be32		*p, *opaque_len;
	struct page	**inpages;
	int		first;
	struct kvec	*iov;

	status = -EIO;
	p = xdr_reserve_space(xdr, 2 * sizeof(*p));
	if (!p)
		goto wrap_failed;
	opaque_len = p++;
	*p = cpu_to_be32(rqstp->rq_seqno);

	if (rpcauth_wrap_req_encode(task, xdr))
		goto wrap_failed;

	status = alloc_enc_pages(rqstp);
	if (unlikely(status))
		goto wrap_failed;
	first = snd_buf->page_base >> PAGE_SHIFT;
	inpages = snd_buf->pages + first;
	snd_buf->pages = rqstp->rq_enc_pages;
	snd_buf->page_base -= first << PAGE_SHIFT;
	/*
	 * Move the tail into its own page, in case gss_wrap needs
	 * more space in the head when wrapping.
	 *
	 * Still... Why can't gss_wrap just slide the tail down?
	 */
	if (snd_buf->page_len || snd_buf->tail[0].iov_len) {
		char *tmp;

		tmp = page_address(rqstp->rq_enc_pages[rqstp->rq_enc_pages_num - 1]);
		memcpy(tmp, snd_buf->tail[0].iov_base, snd_buf->tail[0].iov_len);
		snd_buf->tail[0].iov_base = tmp;
	}
	offset = (u8 *)p - (u8 *)snd_buf->head[0].iov_base;
	maj_stat = gss_wrap(ctx->gc_gss_ctx, offset, snd_buf, inpages);
	/* slack space should prevent this ever happening: */
	if (unlikely(snd_buf->len > snd_buf->buflen))
		goto wrap_failed;
	/* We're assuming that when GSS_S_CONTEXT_EXPIRED, the encryption was
	 * done anyway, so it's safe to put the request on the wire: */
	if (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	else if (maj_stat)
		goto bad_wrap;

	*opaque_len = cpu_to_be32(snd_buf->len - offset);
	/* guess whether the pad goes into the head or the tail: */
	if (snd_buf->page_len || snd_buf->tail[0].iov_len)
		iov = snd_buf->tail;
	else
		iov = snd_buf->head;
	p = iov->iov_base + iov->iov_len;
	pad = 3 - ((snd_buf->len - offset - 1) & 3);
	memset(p, 0, pad);
	iov->iov_len += pad;
	snd_buf->len += pad;

	return 0;
wrap_failed:
	return status;
bad_wrap:
	trace_rpcgss_wrap(task, maj_stat);
	return -EIO;
}
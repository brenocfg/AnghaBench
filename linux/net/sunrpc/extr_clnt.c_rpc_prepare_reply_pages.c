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
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; TYPE_2__* rq_cred; } ;
struct page {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cr_auth; } ;
struct TYPE_3__ {int au_ralign; } ;

/* Variables and functions */
 int RPC_REPHDRSIZE ; 
 int /*<<< orphan*/  trace_rpc_reply_pages (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xdr_inline_pages (int /*<<< orphan*/ *,unsigned int,struct page**,unsigned int,unsigned int) ; 

void rpc_prepare_reply_pages(struct rpc_rqst *req, struct page **pages,
			     unsigned int base, unsigned int len,
			     unsigned int hdrsize)
{
	/* Subtract one to force an extra word of buffer space for the
	 * payload's XDR pad to fall into the rcv_buf's tail iovec.
	 */
	hdrsize += RPC_REPHDRSIZE + req->rq_cred->cr_auth->au_ralign - 1;

	xdr_inline_pages(&req->rq_rcv_buf, hdrsize << 2, pages, base, len);
	trace_rpc_reply_pages(req);
}
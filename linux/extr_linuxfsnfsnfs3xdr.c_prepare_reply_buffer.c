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
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; TYPE_1__* rq_cred; } ;
struct rpc_auth {unsigned int au_rslack; } ;
struct page {int dummy; } ;
struct TYPE_2__ {struct rpc_auth* cr_auth; } ;

/* Variables and functions */
 unsigned int RPC_REPHDRSIZE ; 
 int /*<<< orphan*/  xdr_inline_pages (int /*<<< orphan*/ *,unsigned int,struct page**,unsigned int,unsigned int) ; 

__attribute__((used)) static void prepare_reply_buffer(struct rpc_rqst *req, struct page **pages,
				 unsigned int base, unsigned int len,
				 unsigned int bufsize)
{
	struct rpc_auth	*auth = req->rq_cred->cr_auth;
	unsigned int replen;

	replen = RPC_REPHDRSIZE + auth->au_rslack + bufsize;
	xdr_inline_pages(&req->rq_rcv_buf, replen << 2, pages, base, len);
}
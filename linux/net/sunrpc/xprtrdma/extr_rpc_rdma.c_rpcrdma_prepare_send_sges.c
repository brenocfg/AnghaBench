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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_buf {int dummy; } ;
struct rpcrdma_xprt {int dummy; } ;
struct rpcrdma_req {int /*<<< orphan*/  rl_slot; int /*<<< orphan*/  rl_kref; TYPE_2__* rl_sendctx; } ;
typedef  enum rpcrdma_chunktype { ____Placeholder_rpcrdma_chunktype } rpcrdma_chunktype ;
struct TYPE_3__ {scalar_t__ num_sge; } ;
struct TYPE_4__ {struct rpcrdma_req* sc_req; scalar_t__ sc_unmap_count; TYPE_1__ sc_wr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int rpcrdma_areadch ; 
 int /*<<< orphan*/  rpcrdma_prepare_hdr_sge (struct rpcrdma_xprt*,struct rpcrdma_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrdma_prepare_msg_sges (struct rpcrdma_xprt*,struct rpcrdma_req*,struct xdr_buf*,int) ; 
 TYPE_2__* rpcrdma_sendctx_get_locked (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  trace_xprtrdma_prepsend_failed (int /*<<< orphan*/ *,int) ; 

int
rpcrdma_prepare_send_sges(struct rpcrdma_xprt *r_xprt,
			  struct rpcrdma_req *req, u32 hdrlen,
			  struct xdr_buf *xdr, enum rpcrdma_chunktype rtype)
{
	int ret;

	ret = -EAGAIN;
	req->rl_sendctx = rpcrdma_sendctx_get_locked(r_xprt);
	if (!req->rl_sendctx)
		goto err;
	req->rl_sendctx->sc_wr.num_sge = 0;
	req->rl_sendctx->sc_unmap_count = 0;
	req->rl_sendctx->sc_req = req;
	kref_init(&req->rl_kref);

	ret = -EIO;
	if (!rpcrdma_prepare_hdr_sge(r_xprt, req, hdrlen))
		goto err;
	if (rtype != rpcrdma_areadch)
		if (!rpcrdma_prepare_msg_sges(r_xprt, req, xdr, rtype))
			goto err;
	return 0;

err:
	trace_xprtrdma_prepsend_failed(&req->rl_slot, ret);
	return ret;
}
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
struct xdr_buf {TYPE_1__* head; } ;
struct rpc_rqst {struct xdr_buf rq_snd_buf; struct xdr_buf rq_rcv_buf; int /*<<< orphan*/  rq_bc_pa_state; } ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_BC_PA_IN_USE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_rqst*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct rpc_rqst*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xprt_free_allocation(struct rpc_rqst *req)
{
	struct xdr_buf *xbufp;

	dprintk("RPC:        free allocations for req= %p\n", req);
	WARN_ON_ONCE(test_bit(RPC_BC_PA_IN_USE, &req->rq_bc_pa_state));
	xbufp = &req->rq_rcv_buf;
	free_page((unsigned long)xbufp->head[0].iov_base);
	xbufp = &req->rq_snd_buf;
	free_page((unsigned long)xbufp->head[0].iov_base);
	kfree(req);
}
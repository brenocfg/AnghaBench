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
struct svcxprt_rdma {int dummy; } ;
struct svc_rdma_send_ctxt {void** sc_xprt_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  rb_bc_max_requests; } ;
struct rpcrdma_xprt {TYPE_1__ rx_buf; } ;
struct rpc_xprt {int dummy; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_xid; struct rpc_xprt* rq_xprt; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  RPCRDMA_HDRLEN_MIN ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  rdma_msg ; 
 int /*<<< orphan*/  rpcrdma_version ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (struct rpc_xprt*) ; 
 int svc_rdma_bc_sendto (struct svcxprt_rdma*,struct rpc_rqst*,struct svc_rdma_send_ctxt*) ; 
 struct svc_rdma_send_ctxt* svc_rdma_send_ctxt_get (struct svcxprt_rdma*) ; 
 int /*<<< orphan*/  svc_rdma_send_ctxt_put (struct svcxprt_rdma*,struct svc_rdma_send_ctxt*) ; 
 int /*<<< orphan*/  svc_rdma_sync_reply_hdr (struct svcxprt_rdma*,struct svc_rdma_send_ctxt*,int /*<<< orphan*/ ) ; 
 void* xdr_zero ; 
 int /*<<< orphan*/  xprt_disconnect_done (struct rpc_xprt*) ; 

__attribute__((used)) static int
rpcrdma_bc_send_request(struct svcxprt_rdma *rdma, struct rpc_rqst *rqst)
{
	struct rpc_xprt *xprt = rqst->rq_xprt;
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	struct svc_rdma_send_ctxt *ctxt;
	__be32 *p;
	int rc;

	ctxt = svc_rdma_send_ctxt_get(rdma);
	if (!ctxt)
		goto drop_connection;

	p = ctxt->sc_xprt_buf;
	*p++ = rqst->rq_xid;
	*p++ = rpcrdma_version;
	*p++ = cpu_to_be32(r_xprt->rx_buf.rb_bc_max_requests);
	*p++ = rdma_msg;
	*p++ = xdr_zero;
	*p++ = xdr_zero;
	*p   = xdr_zero;
	svc_rdma_sync_reply_hdr(rdma, ctxt, RPCRDMA_HDRLEN_MIN);

#ifdef SVCRDMA_BACKCHANNEL_DEBUG
	pr_info("%s: %*ph\n", __func__, 64, rqst->rq_buffer);
#endif

	rc = svc_rdma_bc_sendto(rdma, rqst, ctxt);
	if (rc) {
		svc_rdma_send_ctxt_put(rdma, ctxt);
		goto drop_connection;
	}
	return rc;

drop_connection:
	dprintk("svcrdma: failed to send bc call\n");
	xprt_disconnect_done(xprt);
	return -ENOTCONN;
}
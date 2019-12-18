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
struct svc_rqst {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct svc_rdma_send_ctxt {TYPE_1__ sc_send_wr; int /*<<< orphan*/ * sc_xprt_buf; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  RPCRDMA_HDRLEN_ERR ; 
 int /*<<< orphan*/  err_chunk ; 
 int /*<<< orphan*/  rdma_error ; 
 int /*<<< orphan*/  svc_rdma_save_io_pages (struct svc_rqst*,struct svc_rdma_send_ctxt*) ; 
 int svc_rdma_send (struct svcxprt_rdma*,TYPE_1__*) ; 
 int /*<<< orphan*/  svc_rdma_send_ctxt_put (struct svcxprt_rdma*,struct svc_rdma_send_ctxt*) ; 
 int /*<<< orphan*/  svc_rdma_sync_reply_hdr (struct svcxprt_rdma*,struct svc_rdma_send_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_svcrdma_err_chunk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int svc_rdma_send_error_msg(struct svcxprt_rdma *rdma,
				   struct svc_rdma_send_ctxt *ctxt,
				   struct svc_rqst *rqstp)
{
	__be32 *p;
	int ret;

	p = ctxt->sc_xprt_buf;
	trace_svcrdma_err_chunk(*p);
	p += 3;
	*p++ = rdma_error;
	*p   = err_chunk;
	svc_rdma_sync_reply_hdr(rdma, ctxt, RPCRDMA_HDRLEN_ERR);

	svc_rdma_save_io_pages(rqstp, ctxt);

	ctxt->sc_send_wr.opcode = IB_WR_SEND;
	ret = svc_rdma_send(rdma, &ctxt->sc_send_wr);
	if (ret) {
		svc_rdma_send_ctxt_put(rdma, ctxt);
		return ret;
	}

	return 0;
}
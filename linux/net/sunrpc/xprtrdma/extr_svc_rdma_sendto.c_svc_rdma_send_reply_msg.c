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
struct svcxprt_rdma {int dummy; } ;
struct svc_rqst {int /*<<< orphan*/  rq_res; } ;
struct TYPE_3__ {scalar_t__ invalidate_rkey; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_sge; int /*<<< orphan*/  opcode; TYPE_1__ ex; } ;
struct svc_rdma_send_ctxt {TYPE_2__ sc_send_wr; } ;
struct svc_rdma_recv_ctxt {scalar_t__ rc_inv_rkey; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  IB_WR_SEND_WITH_INV ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int svc_rdma_map_reply_msg (struct svcxprt_rdma*,struct svc_rdma_send_ctxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_rdma_save_io_pages (struct svc_rqst*,struct svc_rdma_send_ctxt*) ; 
 int svc_rdma_send (struct svcxprt_rdma*,TYPE_2__*) ; 

__attribute__((used)) static int svc_rdma_send_reply_msg(struct svcxprt_rdma *rdma,
				   struct svc_rdma_send_ctxt *sctxt,
				   struct svc_rdma_recv_ctxt *rctxt,
				   struct svc_rqst *rqstp,
				   __be32 *wr_lst, __be32 *rp_ch)
{
	int ret;

	if (!rp_ch) {
		ret = svc_rdma_map_reply_msg(rdma, sctxt,
					     &rqstp->rq_res, wr_lst);
		if (ret < 0)
			return ret;
	}

	svc_rdma_save_io_pages(rqstp, sctxt);

	if (rctxt->rc_inv_rkey) {
		sctxt->sc_send_wr.opcode = IB_WR_SEND_WITH_INV;
		sctxt->sc_send_wr.ex.invalidate_rkey = rctxt->rc_inv_rkey;
	} else {
		sctxt->sc_send_wr.opcode = IB_WR_SEND;
	}
	dprintk("svcrdma: posting Send WR with %u sge(s)\n",
		sctxt->sc_send_wr.num_sge);
	return svc_rdma_send(rdma, &sctxt->sc_send_wr);
}
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
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct svc_rdma_send_ctxt {TYPE_1__ sc_send_wr; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_buffer; int /*<<< orphan*/  rq_snd_buf; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int svc_rdma_map_reply_msg (struct svcxprt_rdma*,struct svc_rdma_send_ctxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svc_rdma_send (struct svcxprt_rdma*,TYPE_1__*) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int svc_rdma_bc_sendto(struct svcxprt_rdma *rdma,
			      struct rpc_rqst *rqst,
			      struct svc_rdma_send_ctxt *ctxt)
{
	int ret;

	ret = svc_rdma_map_reply_msg(rdma, ctxt, &rqst->rq_snd_buf, NULL);
	if (ret < 0)
		return -EIO;

	/* Bump page refcnt so Send completion doesn't release
	 * the rq_buffer before all retransmits are complete.
	 */
	get_page(virt_to_page(rqst->rq_buffer));
	ctxt->sc_send_wr.opcode = IB_WR_SEND;
	return svc_rdma_send(rdma, &ctxt->sc_send_wr);
}
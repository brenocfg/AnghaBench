#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct p9_trans_rdma {int /*<<< orphan*/  qp; TYPE_3__* pd; TYPE_2__* cm_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  done; } ;
struct TYPE_5__ {int /*<<< orphan*/  sdata; } ;
struct p9_rdma_context {TYPE_4__ cqe; int /*<<< orphan*/  busa; TYPE_1__ rc; } ;
struct p9_client {int /*<<< orphan*/  msize; struct p9_trans_rdma* trans; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct ib_recv_wr {int num_sge; struct ib_sge* sg_list; TYPE_4__* wr_cqe; int /*<<< orphan*/ * next; } ;
struct TYPE_7__ {int /*<<< orphan*/  local_dma_lkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  recv_done ; 

__attribute__((used)) static int
post_recv(struct p9_client *client, struct p9_rdma_context *c)
{
	struct p9_trans_rdma *rdma = client->trans;
	struct ib_recv_wr wr;
	struct ib_sge sge;

	c->busa = ib_dma_map_single(rdma->cm_id->device,
				    c->rc.sdata, client->msize,
				    DMA_FROM_DEVICE);
	if (ib_dma_mapping_error(rdma->cm_id->device, c->busa))
		goto error;

	c->cqe.done = recv_done;

	sge.addr = c->busa;
	sge.length = client->msize;
	sge.lkey = rdma->pd->local_dma_lkey;

	wr.next = NULL;
	wr.wr_cqe = &c->cqe;
	wr.sg_list = &sge;
	wr.num_sge = 1;
	return ib_post_recv(rdma->qp, &wr, NULL);

 error:
	p9_debug(P9_DEBUG_ERROR, "EIO\n");
	return -EIO;
}
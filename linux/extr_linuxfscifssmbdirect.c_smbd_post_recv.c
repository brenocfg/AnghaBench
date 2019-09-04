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
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; int /*<<< orphan*/  lkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  done; } ;
struct smbd_response {TYPE_4__ sge; TYPE_2__ cqe; int /*<<< orphan*/  packet; } ;
struct smbd_connection {TYPE_3__* id; TYPE_1__* pd; int /*<<< orphan*/  max_receive_size; } ;
struct ib_recv_wr {int num_sge; TYPE_4__* sg_list; int /*<<< orphan*/ * next; TYPE_2__* wr_cqe; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; int /*<<< orphan*/  qp; } ;
struct TYPE_5__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  ERR ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_rdma_recv (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  recv_done ; 
 int /*<<< orphan*/  smbd_disconnect_rdma_connection (struct smbd_connection*) ; 

__attribute__((used)) static int smbd_post_recv(
		struct smbd_connection *info, struct smbd_response *response)
{
	struct ib_recv_wr recv_wr;
	int rc = -EIO;

	response->sge.addr = ib_dma_map_single(
				info->id->device, response->packet,
				info->max_receive_size, DMA_FROM_DEVICE);
	if (ib_dma_mapping_error(info->id->device, response->sge.addr))
		return rc;

	response->sge.length = info->max_receive_size;
	response->sge.lkey = info->pd->local_dma_lkey;

	response->cqe.done = recv_done;

	recv_wr.wr_cqe = &response->cqe;
	recv_wr.next = NULL;
	recv_wr.sg_list = &response->sge;
	recv_wr.num_sge = 1;

	rc = ib_post_recv(info->id->qp, &recv_wr, NULL);
	if (rc) {
		ib_dma_unmap_single(info->id->device, response->sge.addr,
				    response->sge.length, DMA_FROM_DEVICE);
		smbd_disconnect_rdma_connection(info);
		log_rdma_recv(ERR, "ib_post_recv failed rc=%d\n", rc);
	}

	return rc;
}
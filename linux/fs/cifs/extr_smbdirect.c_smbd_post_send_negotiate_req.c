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
struct TYPE_6__ {int /*<<< orphan*/  done; } ;
struct smbd_request {int num_sge; int has_payload; TYPE_4__* sge; TYPE_2__ cqe; struct smbd_connection* info; } ;
struct smbd_negotiate_req {void* max_fragmented_size; void* max_receive_size; void* preferred_send_size; void* credits_requested; scalar_t__ reserved; void* max_version; void* min_version; } ;
struct smbd_connection {int /*<<< orphan*/  request_mempool; TYPE_3__* id; int /*<<< orphan*/  send_pending; TYPE_1__* pd; int /*<<< orphan*/  max_fragmented_recv_size; int /*<<< orphan*/  max_receive_size; int /*<<< orphan*/  max_send_size; int /*<<< orphan*/  send_credit_target; } ;
struct ib_send_wr {int num_sge; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; TYPE_4__* sg_list; TYPE_2__* wr_cqe; int /*<<< orphan*/ * next; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/  addr; int /*<<< orphan*/  lkey; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; int /*<<< orphan*/  qp; } ;
struct TYPE_5__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  SMBD_V1 ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_rdma_send (int /*<<< orphan*/ ,char*,int,...) ; 
 struct smbd_request* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct smbd_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_done ; 
 int /*<<< orphan*/  smbd_disconnect_rdma_connection (struct smbd_connection*) ; 
 struct smbd_negotiate_req* smbd_request_payload (struct smbd_request*) ; 

__attribute__((used)) static int smbd_post_send_negotiate_req(struct smbd_connection *info)
{
	struct ib_send_wr send_wr;
	int rc = -ENOMEM;
	struct smbd_request *request;
	struct smbd_negotiate_req *packet;

	request = mempool_alloc(info->request_mempool, GFP_KERNEL);
	if (!request)
		return rc;

	request->info = info;

	packet = smbd_request_payload(request);
	packet->min_version = cpu_to_le16(SMBD_V1);
	packet->max_version = cpu_to_le16(SMBD_V1);
	packet->reserved = 0;
	packet->credits_requested = cpu_to_le16(info->send_credit_target);
	packet->preferred_send_size = cpu_to_le32(info->max_send_size);
	packet->max_receive_size = cpu_to_le32(info->max_receive_size);
	packet->max_fragmented_size =
		cpu_to_le32(info->max_fragmented_recv_size);

	request->num_sge = 1;
	request->sge[0].addr = ib_dma_map_single(
				info->id->device, (void *)packet,
				sizeof(*packet), DMA_TO_DEVICE);
	if (ib_dma_mapping_error(info->id->device, request->sge[0].addr)) {
		rc = -EIO;
		goto dma_mapping_failed;
	}

	request->sge[0].length = sizeof(*packet);
	request->sge[0].lkey = info->pd->local_dma_lkey;

	ib_dma_sync_single_for_device(
		info->id->device, request->sge[0].addr,
		request->sge[0].length, DMA_TO_DEVICE);

	request->cqe.done = send_done;

	send_wr.next = NULL;
	send_wr.wr_cqe = &request->cqe;
	send_wr.sg_list = request->sge;
	send_wr.num_sge = request->num_sge;
	send_wr.opcode = IB_WR_SEND;
	send_wr.send_flags = IB_SEND_SIGNALED;

	log_rdma_send(INFO, "sge addr=%llx length=%x lkey=%x\n",
		request->sge[0].addr,
		request->sge[0].length, request->sge[0].lkey);

	request->has_payload = false;
	atomic_inc(&info->send_pending);
	rc = ib_post_send(info->id->qp, &send_wr, NULL);
	if (!rc)
		return 0;

	/* if we reach here, post send failed */
	log_rdma_send(ERR, "ib_post_send failed rc=%d\n", rc);
	atomic_dec(&info->send_pending);
	ib_dma_unmap_single(info->id->device, request->sge[0].addr,
		request->sge[0].length, DMA_TO_DEVICE);

	smbd_disconnect_rdma_connection(info);

dma_mapping_failed:
	mempool_free(request, info->request_mempool);
	return rc;
}
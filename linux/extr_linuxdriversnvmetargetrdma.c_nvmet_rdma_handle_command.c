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
typedef  scalar_t__ u16 ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct nvmet_rdma_rsp {int /*<<< orphan*/  req; int /*<<< orphan*/  wait_list; TYPE_4__ send_sge; TYPE_2__* cmd; } ;
struct nvmet_rdma_queue {int /*<<< orphan*/  rsp_wr_wait_lock; int /*<<< orphan*/  rsp_wr_wait_list; int /*<<< orphan*/  nvme_sq; int /*<<< orphan*/  nvme_cq; TYPE_3__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {TYPE_1__* sge; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_rdma_execute_command (struct nvmet_rdma_rsp*) ; 
 scalar_t__ nvmet_rdma_map_sgl (struct nvmet_rdma_rsp*) ; 
 int /*<<< orphan*/  nvmet_rdma_ops ; 
 int /*<<< orphan*/  nvmet_req_complete (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nvmet_req_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nvmet_rdma_handle_command(struct nvmet_rdma_queue *queue,
		struct nvmet_rdma_rsp *cmd)
{
	u16 status;

	ib_dma_sync_single_for_cpu(queue->dev->device,
		cmd->cmd->sge[0].addr, cmd->cmd->sge[0].length,
		DMA_FROM_DEVICE);
	ib_dma_sync_single_for_cpu(queue->dev->device,
		cmd->send_sge.addr, cmd->send_sge.length,
		DMA_TO_DEVICE);

	if (!nvmet_req_init(&cmd->req, &queue->nvme_cq,
			&queue->nvme_sq, &nvmet_rdma_ops))
		return;

	status = nvmet_rdma_map_sgl(cmd);
	if (status)
		goto out_err;

	if (unlikely(!nvmet_rdma_execute_command(cmd))) {
		spin_lock(&queue->rsp_wr_wait_lock);
		list_add_tail(&cmd->wait_list, &queue->rsp_wr_wait_list);
		spin_unlock(&queue->rsp_wr_wait_lock);
	}

	return;

out_err:
	nvmet_req_complete(&cmd->req, status);
}
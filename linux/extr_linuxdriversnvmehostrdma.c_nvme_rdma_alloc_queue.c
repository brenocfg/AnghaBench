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
struct sockaddr {int dummy; } ;
struct nvme_rdma_queue {int cmnd_capsule_len; size_t queue_size; int /*<<< orphan*/  cm_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  cm_error; int /*<<< orphan*/  cm_done; struct nvme_rdma_ctrl* ctrl; } ;
struct TYPE_4__ {int ioccsz; int /*<<< orphan*/  device; TYPE_1__* opts; } ;
struct nvme_rdma_ctrl {TYPE_2__ ctrl; int /*<<< orphan*/  addr; int /*<<< orphan*/  src_addr; struct nvme_rdma_queue* queues; } ;
struct nvme_command {int dummy; } ;
struct TYPE_3__ {int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVME_RDMA_CONNECT_TIMEOUT_MS ; 
 int /*<<< orphan*/  NVME_RDMA_Q_ALLOCATED ; 
 int NVMF_OPT_HOST_TRADDR ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  nvme_rdma_cm_handler ; 
 int /*<<< orphan*/  nvme_rdma_destroy_queue_ib (struct nvme_rdma_queue*) ; 
 int nvme_rdma_wait_for_cm (struct nvme_rdma_queue*) ; 
 int /*<<< orphan*/  rdma_create_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nvme_rdma_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ ) ; 
 int rdma_resolve_addr (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_rdma_alloc_queue(struct nvme_rdma_ctrl *ctrl,
		int idx, size_t queue_size)
{
	struct nvme_rdma_queue *queue;
	struct sockaddr *src_addr = NULL;
	int ret;

	queue = &ctrl->queues[idx];
	queue->ctrl = ctrl;
	init_completion(&queue->cm_done);

	if (idx > 0)
		queue->cmnd_capsule_len = ctrl->ctrl.ioccsz * 16;
	else
		queue->cmnd_capsule_len = sizeof(struct nvme_command);

	queue->queue_size = queue_size;

	queue->cm_id = rdma_create_id(&init_net, nvme_rdma_cm_handler, queue,
			RDMA_PS_TCP, IB_QPT_RC);
	if (IS_ERR(queue->cm_id)) {
		dev_info(ctrl->ctrl.device,
			"failed to create CM ID: %ld\n", PTR_ERR(queue->cm_id));
		return PTR_ERR(queue->cm_id);
	}

	if (ctrl->ctrl.opts->mask & NVMF_OPT_HOST_TRADDR)
		src_addr = (struct sockaddr *)&ctrl->src_addr;

	queue->cm_error = -ETIMEDOUT;
	ret = rdma_resolve_addr(queue->cm_id, src_addr,
			(struct sockaddr *)&ctrl->addr,
			NVME_RDMA_CONNECT_TIMEOUT_MS);
	if (ret) {
		dev_info(ctrl->ctrl.device,
			"rdma_resolve_addr failed (%d).\n", ret);
		goto out_destroy_cm_id;
	}

	ret = nvme_rdma_wait_for_cm(queue);
	if (ret) {
		dev_info(ctrl->ctrl.device,
			"rdma connection establishment failed (%d)\n", ret);
		goto out_destroy_cm_id;
	}

	set_bit(NVME_RDMA_Q_ALLOCATED, &queue->flags);

	return 0;

out_destroy_cm_id:
	rdma_destroy_id(queue->cm_id);
	nvme_rdma_destroy_queue_ib(queue);
	return ret;
}
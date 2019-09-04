#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvmet_rdma_device {scalar_t__ srq; int /*<<< orphan*/  device; } ;
struct nvmet_rdma_cmd {int /*<<< orphan*/  wr; TYPE_2__* queue; TYPE_3__* sge; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__* cm_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_post_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ib_post_srq_recv (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvmet_rdma_post_recv(struct nvmet_rdma_device *ndev,
		struct nvmet_rdma_cmd *cmd)
{
	int ret;

	ib_dma_sync_single_for_device(ndev->device,
		cmd->sge[0].addr, cmd->sge[0].length,
		DMA_FROM_DEVICE);

	if (ndev->srq)
		ret = ib_post_srq_recv(ndev->srq, &cmd->wr, NULL);
	else
		ret = ib_post_recv(cmd->queue->cm_id->qp, &cmd->wr, NULL);

	if (unlikely(ret))
		pr_err("post_recv cmd failed\n");

	return ret;
}
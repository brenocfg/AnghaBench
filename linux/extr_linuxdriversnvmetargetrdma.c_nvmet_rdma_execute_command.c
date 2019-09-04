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
struct nvmet_rdma_rsp {int /*<<< orphan*/  req; int /*<<< orphan*/  read_cqe; int /*<<< orphan*/  rw; scalar_t__ n_rdma; struct nvmet_rdma_queue* queue; } ;
struct TYPE_5__ {TYPE_1__* ctrl; } ;
struct nvmet_rdma_queue {TYPE_3__* cm_id; int /*<<< orphan*/  sq_wr_avail; TYPE_2__ nvme_sq; int /*<<< orphan*/  idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  qp; } ;
struct TYPE_4__ {int /*<<< orphan*/  cntlid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_SC_DATA_XFER_ERROR ; 
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_sub_return (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ nvmet_rdma_need_data_in (struct nvmet_rdma_rsp*) ; 
 int /*<<< orphan*/  nvmet_req_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_req_execute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_rw_ctx_post (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool nvmet_rdma_execute_command(struct nvmet_rdma_rsp *rsp)
{
	struct nvmet_rdma_queue *queue = rsp->queue;

	if (unlikely(atomic_sub_return(1 + rsp->n_rdma,
			&queue->sq_wr_avail) < 0)) {
		pr_debug("IB send queue full (needed %d): queue %u cntlid %u\n",
				1 + rsp->n_rdma, queue->idx,
				queue->nvme_sq.ctrl->cntlid);
		atomic_add(1 + rsp->n_rdma, &queue->sq_wr_avail);
		return false;
	}

	if (nvmet_rdma_need_data_in(rsp)) {
		if (rdma_rw_ctx_post(&rsp->rw, queue->cm_id->qp,
				queue->cm_id->port_num, &rsp->read_cqe, NULL))
			nvmet_req_complete(&rsp->req, NVME_SC_DATA_XFER_ERROR);
	} else {
		nvmet_req_execute(&rsp->req);
	}

	return true;
}
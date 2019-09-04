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
struct TYPE_6__ {int /*<<< orphan*/  done; } ;
struct nvme_rdma_request {TYPE_3__ reg_cqe; TYPE_1__* mr; } ;
struct nvme_rdma_queue {int /*<<< orphan*/  qp; } ;
struct TYPE_5__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct ib_send_wr {TYPE_3__* wr_cqe; TYPE_2__ ex; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  num_sge; int /*<<< orphan*/ * next; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {int /*<<< orphan*/  rkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_LOCAL_INV ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_rdma_inv_rkey_done ; 

__attribute__((used)) static int nvme_rdma_inv_rkey(struct nvme_rdma_queue *queue,
		struct nvme_rdma_request *req)
{
	struct ib_send_wr wr = {
		.opcode		    = IB_WR_LOCAL_INV,
		.next		    = NULL,
		.num_sge	    = 0,
		.send_flags	    = IB_SEND_SIGNALED,
		.ex.invalidate_rkey = req->mr->rkey,
	};

	req->reg_cqe.done = nvme_rdma_inv_rkey_done;
	wr.wr_cqe = &req->reg_cqe;

	return ib_post_send(queue->qp, &wr, NULL);
}
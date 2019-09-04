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
struct nvmet_fc_tgt_queue {int /*<<< orphan*/  work_q; int /*<<< orphan*/  cpu; } ;
struct nvmet_fc_fcp_iod {int /*<<< orphan*/  done_work; TYPE_2__* tgtport; struct nvmet_fc_tgt_queue* queue; } ;
struct nvmefc_tgt_fcp_req {struct nvmet_fc_fcp_iod* nvmet_fc_private; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int target_features; } ;

/* Variables and functions */
 int NVMET_FCTGTFEAT_OPDONE_IN_ISR ; 
 int /*<<< orphan*/  nvmet_fc_fod_op_done (struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvmet_fc_xmt_fcp_op_done(struct nvmefc_tgt_fcp_req *fcpreq)
{
	struct nvmet_fc_fcp_iod *fod = fcpreq->nvmet_fc_private;
	struct nvmet_fc_tgt_queue *queue = fod->queue;

	if (fod->tgtport->ops->target_features & NVMET_FCTGTFEAT_OPDONE_IN_ISR)
		/* context switch so completion is not in ISR context */
		queue_work_on(queue->cpu, queue->work_q, &fod->done_work);
	else
		nvmet_fc_fod_op_done(fod);
}
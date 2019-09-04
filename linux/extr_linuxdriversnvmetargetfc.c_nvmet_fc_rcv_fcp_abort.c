#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvmet_fc_tgt_queue {int /*<<< orphan*/  qlock; } ;
struct nvmet_fc_target_port {int dummy; } ;
struct nvmet_fc_fcp_iod {int abort; int aborted; int /*<<< orphan*/  flock; scalar_t__ active; struct nvmet_fc_tgt_queue* queue; struct nvmefc_tgt_fcp_req* fcpreq; } ;
struct nvmefc_tgt_fcp_req {struct nvmet_fc_fcp_iod* nvmet_fc_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
nvmet_fc_rcv_fcp_abort(struct nvmet_fc_target_port *target_port,
			struct nvmefc_tgt_fcp_req *fcpreq)
{
	struct nvmet_fc_fcp_iod *fod = fcpreq->nvmet_fc_private;
	struct nvmet_fc_tgt_queue *queue;
	unsigned long flags;

	if (!fod || fod->fcpreq != fcpreq)
		/* job appears to have already completed, ignore abort */
		return;

	queue = fod->queue;

	spin_lock_irqsave(&queue->qlock, flags);
	if (fod->active) {
		/*
		 * mark as abort. The abort handler, invoked upon completion
		 * of any work, will detect the aborted status and do the
		 * callback.
		 */
		spin_lock(&fod->flock);
		fod->abort = true;
		fod->aborted = true;
		spin_unlock(&fod->flock);
	}
	spin_unlock_irqrestore(&queue->qlock, flags);
}
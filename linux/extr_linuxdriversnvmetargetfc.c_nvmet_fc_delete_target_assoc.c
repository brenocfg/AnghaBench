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
struct nvmet_fc_tgtport {int /*<<< orphan*/  lock; } ;
struct nvmet_fc_tgt_queue {int dummy; } ;
struct nvmet_fc_tgt_assoc {struct nvmet_fc_tgt_queue** queues; struct nvmet_fc_tgtport* tgtport; } ;

/* Variables and functions */
 int NVMET_NR_QUEUES ; 
 int /*<<< orphan*/  nvmet_fc_delete_target_queue (struct nvmet_fc_tgt_queue*) ; 
 int /*<<< orphan*/  nvmet_fc_tgt_a_put (struct nvmet_fc_tgt_assoc*) ; 
 int /*<<< orphan*/  nvmet_fc_tgt_q_get (struct nvmet_fc_tgt_queue*) ; 
 int /*<<< orphan*/  nvmet_fc_tgt_q_put (struct nvmet_fc_tgt_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nvmet_fc_delete_target_assoc(struct nvmet_fc_tgt_assoc *assoc)
{
	struct nvmet_fc_tgtport *tgtport = assoc->tgtport;
	struct nvmet_fc_tgt_queue *queue;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&tgtport->lock, flags);
	for (i = NVMET_NR_QUEUES; i >= 0; i--) {
		queue = assoc->queues[i];
		if (queue) {
			if (!nvmet_fc_tgt_q_get(queue))
				continue;
			spin_unlock_irqrestore(&tgtport->lock, flags);
			nvmet_fc_delete_target_queue(queue);
			nvmet_fc_tgt_q_put(queue);
			spin_lock_irqsave(&tgtport->lock, flags);
		}
	}
	spin_unlock_irqrestore(&tgtport->lock, flags);

	nvmet_fc_tgt_a_put(assoc);
}
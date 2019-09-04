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
struct viosrp_crq {scalar_t__ valid; } ;
struct crq_queue {size_t cur; size_t size; int /*<<< orphan*/  lock; struct viosrp_crq* msgs; } ;

/* Variables and functions */
 scalar_t__ VIOSRP_CRQ_FREE ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct viosrp_crq *crq_queue_next_crq(struct crq_queue *queue)
{
	struct viosrp_crq *crq;
	unsigned long flags;

	spin_lock_irqsave(&queue->lock, flags);
	crq = &queue->msgs[queue->cur];
	if (crq->valid != VIOSRP_CRQ_FREE) {
		if (++queue->cur == queue->size)
			queue->cur = 0;

		/* Ensure the read of the valid bit occurs before reading any
		 * other bits of the CRQ entry
		 */
		rmb();
	} else
		crq = NULL;
	spin_unlock_irqrestore(&queue->lock, flags);

	return crq;
}
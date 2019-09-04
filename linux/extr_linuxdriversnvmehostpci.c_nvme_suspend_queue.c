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
struct nvme_queue {int cq_vector; TYPE_2__* dev; int /*<<< orphan*/  qid; int /*<<< orphan*/  cq_lock; } ;
struct TYPE_3__ {scalar_t__ admin_q; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ ctrl; int /*<<< orphan*/  online_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_quiesce_queue (scalar_t__) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pci_free_irq (int /*<<< orphan*/ ,int,struct nvme_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_suspend_queue(struct nvme_queue *nvmeq)
{
	int vector;

	spin_lock_irq(&nvmeq->cq_lock);
	if (nvmeq->cq_vector == -1) {
		spin_unlock_irq(&nvmeq->cq_lock);
		return 1;
	}
	vector = nvmeq->cq_vector;
	nvmeq->dev->online_queues--;
	nvmeq->cq_vector = -1;
	spin_unlock_irq(&nvmeq->cq_lock);

	/*
	 * Ensure that nvme_queue_rq() sees it ->cq_vector == -1 without
	 * having to grab the lock.
	 */
	mb();

	if (!nvmeq->qid && nvmeq->dev->ctrl.admin_q)
		blk_mq_quiesce_queue(nvmeq->dev->ctrl.admin_q);

	pci_free_irq(to_pci_dev(nvmeq->dev->dev), vector, nvmeq);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct nvme_queue {int /*<<< orphan*/  cq_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  cap; } ;
struct nvme_dev {TYPE_1__ ctrl; struct nvme_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_complete_cqes (struct nvme_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_disable_ctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_process_cq (struct nvme_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvme_shutdown_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_disable_admin_queue(struct nvme_dev *dev, bool shutdown)
{
	struct nvme_queue *nvmeq = &dev->queues[0];
	u16 start, end;

	if (shutdown)
		nvme_shutdown_ctrl(&dev->ctrl);
	else
		nvme_disable_ctrl(&dev->ctrl, dev->ctrl.cap);

	spin_lock_irq(&nvmeq->cq_lock);
	nvme_process_cq(nvmeq, &start, &end, -1);
	spin_unlock_irq(&nvmeq->cq_lock);

	nvme_complete_cqes(nvmeq, start, end);
}
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
typedef  int /*<<< orphan*/  u16 ;
struct nvme_queue {int /*<<< orphan*/  cq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_complete_cqes (struct nvme_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cqe_pending (struct nvme_queue*) ; 
 int nvme_process_cq (struct nvme_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __nvme_poll(struct nvme_queue *nvmeq, unsigned int tag)
{
	u16 start, end;
	bool found;

	if (!nvme_cqe_pending(nvmeq))
		return 0;

	spin_lock_irq(&nvmeq->cq_lock);
	found = nvme_process_cq(nvmeq, &start, &end, tag);
	spin_unlock_irq(&nvmeq->cq_lock);

	nvme_complete_cqes(nvmeq, start, end);
	return found;
}
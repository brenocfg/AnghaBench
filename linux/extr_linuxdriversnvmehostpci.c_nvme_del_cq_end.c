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
struct request {struct nvme_queue* end_io_data; } ;
struct nvme_queue {int /*<<< orphan*/  cq_lock; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_complete_cqes (struct nvme_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_del_queue_end (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_process_cq (struct nvme_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nvme_del_cq_end(struct request *req, blk_status_t error)
{
	struct nvme_queue *nvmeq = req->end_io_data;
	u16 start, end;

	if (!error) {
		unsigned long flags;

		spin_lock_irqsave(&nvmeq->cq_lock, flags);
		nvme_process_cq(nvmeq, &start, &end, -1);
		spin_unlock_irqrestore(&nvmeq->cq_lock, flags);

		nvme_complete_cqes(nvmeq, start, end);
	}

	nvme_del_queue_end(req, error);
}
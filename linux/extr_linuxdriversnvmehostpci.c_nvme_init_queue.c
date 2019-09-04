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
typedef  int u16 ;
struct nvme_queue {int cq_phase; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  q_depth; scalar_t__ cqes; int /*<<< orphan*/ * q_db; scalar_t__ cq_head; scalar_t__ sq_tail; struct nvme_dev* dev; } ;
struct nvme_dev {int db_stride; int /*<<< orphan*/  online_queues; int /*<<< orphan*/ * dbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_dbbuf_init (struct nvme_dev*,struct nvme_queue*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_init_queue(struct nvme_queue *nvmeq, u16 qid)
{
	struct nvme_dev *dev = nvmeq->dev;

	spin_lock_irq(&nvmeq->cq_lock);
	nvmeq->sq_tail = 0;
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	nvmeq->q_db = &dev->dbs[qid * 2 * dev->db_stride];
	memset((void *)nvmeq->cqes, 0, CQ_SIZE(nvmeq->q_depth));
	nvme_dbbuf_init(dev, nvmeq, qid);
	dev->online_queues++;
	spin_unlock_irq(&nvmeq->cq_lock);
}
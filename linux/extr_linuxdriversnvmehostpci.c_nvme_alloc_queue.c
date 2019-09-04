#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvme_queue {int cq_phase; int q_depth; int qid; int cq_vector; int /*<<< orphan*/  cq_dma_addr; scalar_t__ cqes; int /*<<< orphan*/ * q_db; scalar_t__ cq_head; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  sq_lock; struct nvme_dev* dev; int /*<<< orphan*/  q_dmadev; } ;
struct TYPE_2__ {int queue_count; } ;
struct nvme_dev {int db_stride; int /*<<< orphan*/  dev; TYPE_1__ ctrl; int /*<<< orphan*/ * dbs; struct nvme_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_SIZE (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_zalloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvme_alloc_sq_cmds (struct nvme_dev*,struct nvme_queue*,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_alloc_queue(struct nvme_dev *dev, int qid, int depth)
{
	struct nvme_queue *nvmeq = &dev->queues[qid];

	if (dev->ctrl.queue_count > qid)
		return 0;

	nvmeq->cqes = dma_zalloc_coherent(dev->dev, CQ_SIZE(depth),
					  &nvmeq->cq_dma_addr, GFP_KERNEL);
	if (!nvmeq->cqes)
		goto free_nvmeq;

	if (nvme_alloc_sq_cmds(dev, nvmeq, qid, depth))
		goto free_cqdma;

	nvmeq->q_dmadev = dev->dev;
	nvmeq->dev = dev;
	spin_lock_init(&nvmeq->sq_lock);
	spin_lock_init(&nvmeq->cq_lock);
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	nvmeq->q_db = &dev->dbs[qid * 2 * dev->db_stride];
	nvmeq->q_depth = depth;
	nvmeq->qid = qid;
	nvmeq->cq_vector = -1;
	dev->ctrl.queue_count++;

	return 0;

 free_cqdma:
	dma_free_coherent(dev->dev, CQ_SIZE(depth), (void *)nvmeq->cqes,
							nvmeq->cq_dma_addr);
 free_nvmeq:
	return -ENOMEM;
}
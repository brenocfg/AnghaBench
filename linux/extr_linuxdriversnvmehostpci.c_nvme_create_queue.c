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
struct nvme_queue {int cq_vector; scalar_t__ sq_cmds_io; scalar_t__ sq_dma_addr; int /*<<< orphan*/  q_depth; struct nvme_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_size; } ;
struct nvme_dev {int cmbsz; int num_vecs; int /*<<< orphan*/  online_queues; scalar_t__ cmb; scalar_t__ cmb_bus_addr; TYPE_1__ ctrl; } ;
typedef  int s16 ;

/* Variables and functions */
 int NVME_CMBSZ_SQS ; 
 int /*<<< orphan*/  SQ_SIZE (int /*<<< orphan*/ ) ; 
 int adapter_alloc_cq (struct nvme_dev*,int,struct nvme_queue*,int) ; 
 int adapter_alloc_sq (struct nvme_dev*,int,struct nvme_queue*) ; 
 int /*<<< orphan*/  adapter_delete_cq (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  adapter_delete_sq (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  nvme_init_queue (struct nvme_queue*,int) ; 
 int queue_request_irq (struct nvme_queue*) ; 
 int roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ use_cmb_sqes ; 

__attribute__((used)) static int nvme_create_queue(struct nvme_queue *nvmeq, int qid)
{
	struct nvme_dev *dev = nvmeq->dev;
	int result;
	s16 vector;

	if (dev->cmb && use_cmb_sqes && (dev->cmbsz & NVME_CMBSZ_SQS)) {
		unsigned offset = (qid - 1) * roundup(SQ_SIZE(nvmeq->q_depth),
						      dev->ctrl.page_size);
		nvmeq->sq_dma_addr = dev->cmb_bus_addr + offset;
		nvmeq->sq_cmds_io = dev->cmb + offset;
	}

	/*
	 * A queue's vector matches the queue identifier unless the controller
	 * has only one vector available.
	 */
	vector = dev->num_vecs == 1 ? 0 : qid;
	result = adapter_alloc_cq(dev, qid, nvmeq, vector);
	if (result)
		return result;

	result = adapter_alloc_sq(dev, qid, nvmeq);
	if (result < 0)
		return result;
	else if (result)
		goto release_cq;

	/*
	 * Set cq_vector after alloc cq/sq, otherwise nvme_suspend_queue will
	 * invoke free_irq for it and cause a 'Trying to free already-free IRQ
	 * xxx' warning if the create CQ/SQ command times out.
	 */
	nvmeq->cq_vector = vector;
	nvme_init_queue(nvmeq, qid);
	result = queue_request_irq(nvmeq);
	if (result < 0)
		goto release_sq;

	return result;

release_sq:
	nvmeq->cq_vector = -1;
	dev->online_queues--;
	adapter_delete_sq(dev, qid);
release_cq:
	adapter_delete_cq(dev, qid);
	return result;
}
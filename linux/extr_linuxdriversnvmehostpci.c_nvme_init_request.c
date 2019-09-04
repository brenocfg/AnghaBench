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
struct request {int dummy; } ;
struct nvme_queue {int dummy; } ;
struct nvme_iod {struct nvme_queue* nvmeq; } ;
struct blk_mq_tag_set {struct nvme_dev* driver_data; } ;
struct nvme_dev {int /*<<< orphan*/  ctrl; struct nvme_queue* queues; struct blk_mq_tag_set tagset; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 TYPE_1__* nvme_req (struct request*) ; 

__attribute__((used)) static int nvme_init_request(struct blk_mq_tag_set *set, struct request *req,
		unsigned int hctx_idx, unsigned int numa_node)
{
	struct nvme_dev *dev = set->driver_data;
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	int queue_idx = (set == &dev->tagset) ? hctx_idx + 1 : 0;
	struct nvme_queue *nvmeq = &dev->queues[queue_idx];

	BUG_ON(!nvmeq);
	iod->nvmeq = nvmeq;

	nvme_req(req)->ctrl = &dev->ctrl;
	return 0;
}
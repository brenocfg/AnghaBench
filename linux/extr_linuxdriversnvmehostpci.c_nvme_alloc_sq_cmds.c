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
struct nvme_queue {int /*<<< orphan*/  sq_cmds; int /*<<< orphan*/  sq_dma_addr; } ;
struct nvme_dev {int cmbsz; int /*<<< orphan*/  dev; scalar_t__ cmb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NVME_CMBSZ_SQS ; 
 int /*<<< orphan*/  SQ_SIZE (int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ use_cmb_sqes ; 

__attribute__((used)) static int nvme_alloc_sq_cmds(struct nvme_dev *dev, struct nvme_queue *nvmeq,
				int qid, int depth)
{
	/* CMB SQEs will be mapped before creation */
	if (qid && dev->cmb && use_cmb_sqes && (dev->cmbsz & NVME_CMBSZ_SQS))
		return 0;

	nvmeq->sq_cmds = dma_alloc_coherent(dev->dev, SQ_SIZE(depth),
					    &nvmeq->sq_dma_addr, GFP_KERNEL);
	if (!nvmeq->sq_cmds)
		return -ENOMEM;
	return 0;
}
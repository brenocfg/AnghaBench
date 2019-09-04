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
struct request {int dummy; } ;
struct nvme_iod {int npages; unsigned int length; scalar_t__ nents; scalar_t__ aborted; scalar_t__ inline_sg; scalar_t__ sg; int /*<<< orphan*/  use_sgl; } ;
struct nvme_dev {int /*<<< orphan*/  iod_mempool; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int NVME_INT_BYTES (struct nvme_dev*) ; 
 int NVME_INT_PAGES ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int blk_rq_nr_phys_segments (struct request*) ; 
 unsigned int blk_rq_payload_bytes (struct request*) ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_pci_use_sgls (struct nvme_dev*,struct request*) ; 

__attribute__((used)) static blk_status_t nvme_init_iod(struct request *rq, struct nvme_dev *dev)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(rq);
	int nseg = blk_rq_nr_phys_segments(rq);
	unsigned int size = blk_rq_payload_bytes(rq);

	iod->use_sgl = nvme_pci_use_sgls(dev, rq);

	if (nseg > NVME_INT_PAGES || size > NVME_INT_BYTES(dev)) {
		iod->sg = mempool_alloc(dev->iod_mempool, GFP_ATOMIC);
		if (!iod->sg)
			return BLK_STS_RESOURCE;
	} else {
		iod->sg = iod->inline_sg;
	}

	iod->aborted = 0;
	iod->npages = -1;
	iod->nents = 0;
	iod->length = size;

	return BLK_STS_OK;
}
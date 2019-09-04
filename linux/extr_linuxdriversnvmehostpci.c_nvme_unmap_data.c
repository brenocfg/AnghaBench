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
struct nvme_iod {int nents; int /*<<< orphan*/  meta_sg; int /*<<< orphan*/ * sg; } ;
struct nvme_dev {int /*<<< orphan*/  dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (struct request*) ; 
 int /*<<< orphan*/  nvme_free_iod (struct nvme_dev*,struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static void nvme_unmap_data(struct nvme_dev *dev, struct request *req)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	enum dma_data_direction dma_dir = rq_data_dir(req) ?
			DMA_TO_DEVICE : DMA_FROM_DEVICE;

	if (iod->nents) {
		dma_unmap_sg(dev->dev, iod->sg, iod->nents, dma_dir);
		if (blk_integrity_rq(req))
			dma_unmap_sg(dev->dev, &iod->meta_sg, 1, dma_dir);
	}

	nvme_cleanup_cmd(req);
	nvme_free_iod(dev, req);
}
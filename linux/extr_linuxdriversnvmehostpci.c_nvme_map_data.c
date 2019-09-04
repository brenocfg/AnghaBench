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
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/  bio; struct request_queue* q; } ;
struct nvme_iod {int /*<<< orphan*/  nents; int /*<<< orphan*/ * sg; int /*<<< orphan*/  meta_sg; scalar_t__ use_sgl; } ;
struct nvme_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  metadata; } ;
struct nvme_command {TYPE_1__ rw; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  DMA_ATTR_NO_WARN ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int blk_rq_count_integrity_sg (struct request_queue*,int /*<<< orphan*/ ) ; 
 int blk_rq_map_integrity_sg (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_rq_map_sg (struct request_queue*,struct request*,int /*<<< orphan*/ *) ; 
 int blk_rq_nr_phys_segments (struct request*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int dma_map_sg_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_pci_setup_prps (struct nvme_dev*,struct request*,TYPE_1__*) ; 
 scalar_t__ nvme_pci_setup_sgls (struct nvme_dev*,struct request*,TYPE_1__*,int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static blk_status_t nvme_map_data(struct nvme_dev *dev, struct request *req,
		struct nvme_command *cmnd)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	struct request_queue *q = req->q;
	enum dma_data_direction dma_dir = rq_data_dir(req) ?
			DMA_TO_DEVICE : DMA_FROM_DEVICE;
	blk_status_t ret = BLK_STS_IOERR;
	int nr_mapped;

	sg_init_table(iod->sg, blk_rq_nr_phys_segments(req));
	iod->nents = blk_rq_map_sg(q, req, iod->sg);
	if (!iod->nents)
		goto out;

	ret = BLK_STS_RESOURCE;
	nr_mapped = dma_map_sg_attrs(dev->dev, iod->sg, iod->nents, dma_dir,
			DMA_ATTR_NO_WARN);
	if (!nr_mapped)
		goto out;

	if (iod->use_sgl)
		ret = nvme_pci_setup_sgls(dev, req, &cmnd->rw, nr_mapped);
	else
		ret = nvme_pci_setup_prps(dev, req, &cmnd->rw);

	if (ret != BLK_STS_OK)
		goto out_unmap;

	ret = BLK_STS_IOERR;
	if (blk_integrity_rq(req)) {
		if (blk_rq_count_integrity_sg(q, req->bio) != 1)
			goto out_unmap;

		sg_init_table(&iod->meta_sg, 1);
		if (blk_rq_map_integrity_sg(q, req->bio, &iod->meta_sg) != 1)
			goto out_unmap;

		if (!dma_map_sg(dev->dev, &iod->meta_sg, 1, dma_dir))
			goto out_unmap;
	}

	if (blk_integrity_rq(req))
		cmnd->rw.metadata = cpu_to_le64(sg_dma_address(&iod->meta_sg));
	return BLK_STS_OK;

out_unmap:
	dma_unmap_sg(dev->dev, iod->sg, iod->nents, dma_dir);
out:
	return ret;
}
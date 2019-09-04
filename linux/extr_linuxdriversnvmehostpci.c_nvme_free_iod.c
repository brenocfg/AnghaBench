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
struct nvme_sgl_desc {int /*<<< orphan*/  addr; } ;
struct nvme_iod {int npages; scalar_t__ sg; scalar_t__ inline_sg; scalar_t__ use_sgl; int /*<<< orphan*/  first_dma; } ;
struct TYPE_2__ {int page_size; } ;
struct nvme_dev {int /*<<< orphan*/  iod_mempool; int /*<<< orphan*/  prp_page_pool; int /*<<< orphan*/  prp_small_pool; TYPE_1__ ctrl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int SGES_PER_PAGE ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (scalar_t__,int /*<<< orphan*/ ) ; 
 void** nvme_pci_iod_list (struct request*) ; 

__attribute__((used)) static void nvme_free_iod(struct nvme_dev *dev, struct request *req)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	const int last_prp = dev->ctrl.page_size / sizeof(__le64) - 1;
	dma_addr_t dma_addr = iod->first_dma, next_dma_addr;

	int i;

	if (iod->npages == 0)
		dma_pool_free(dev->prp_small_pool, nvme_pci_iod_list(req)[0],
			dma_addr);

	for (i = 0; i < iod->npages; i++) {
		void *addr = nvme_pci_iod_list(req)[i];

		if (iod->use_sgl) {
			struct nvme_sgl_desc *sg_list = addr;

			next_dma_addr =
			    le64_to_cpu((sg_list[SGES_PER_PAGE - 1]).addr);
		} else {
			__le64 *prp_list = addr;

			next_dma_addr = le64_to_cpu(prp_list[last_prp]);
		}

		dma_pool_free(dev->prp_page_pool, addr, dma_addr);
		dma_addr = next_dma_addr;
	}

	if (iod->sg != iod->inline_sg)
		mempool_free(iod->sg, dev->iod_mempool);
}
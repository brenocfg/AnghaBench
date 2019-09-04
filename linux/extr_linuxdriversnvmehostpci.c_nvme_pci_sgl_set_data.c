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
struct scatterlist {int dummy; } ;
struct nvme_sgl_desc {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int NVME_SGL_FMT_DATA_DESC ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static void nvme_pci_sgl_set_data(struct nvme_sgl_desc *sge,
		struct scatterlist *sg)
{
	sge->addr = cpu_to_le64(sg_dma_address(sg));
	sge->length = cpu_to_le32(sg_dma_len(sg));
	sge->type = NVME_SGL_FMT_DATA_DESC << 4;
}
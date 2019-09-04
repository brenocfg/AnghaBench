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
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct scatterlist {int dummy; } ;
struct mvumi_sgl {unsigned int flags; void* baseaddr_h; void* baseaddr_l; } ;
struct mvumi_hba {unsigned char max_sge; unsigned int eot_flag; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 unsigned char pci_map_sg (TYPE_1__*,struct scatterlist*,unsigned int,int) ; 
 int /*<<< orphan*/  pci_unmap_sg (TYPE_1__*,struct scatterlist*,unsigned int,int) ; 
 unsigned int scsi_sg_count (struct scsi_cmnd*) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  sgd_inc (struct mvumi_hba*,struct mvumi_sgl*) ; 
 int /*<<< orphan*/  sgd_setsz (struct mvumi_hba*,struct mvumi_sgl*,void*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvumi_make_sgl(struct mvumi_hba *mhba, struct scsi_cmnd *scmd,
					void *sgl_p, unsigned char *sg_count)
{
	struct scatterlist *sg;
	struct mvumi_sgl *m_sg = (struct mvumi_sgl *) sgl_p;
	unsigned int i;
	unsigned int sgnum = scsi_sg_count(scmd);
	dma_addr_t busaddr;

	sg = scsi_sglist(scmd);
	*sg_count = pci_map_sg(mhba->pdev, sg, sgnum,
			       (int) scmd->sc_data_direction);
	if (*sg_count > mhba->max_sge) {
		dev_err(&mhba->pdev->dev,
			"sg count[0x%x] is bigger than max sg[0x%x].\n",
			*sg_count, mhba->max_sge);
		pci_unmap_sg(mhba->pdev, sg, sgnum,
			     (int) scmd->sc_data_direction);
		return -1;
	}
	for (i = 0; i < *sg_count; i++) {
		busaddr = sg_dma_address(&sg[i]);
		m_sg->baseaddr_l = cpu_to_le32(lower_32_bits(busaddr));
		m_sg->baseaddr_h = cpu_to_le32(upper_32_bits(busaddr));
		m_sg->flags = 0;
		sgd_setsz(mhba, m_sg, cpu_to_le32(sg_dma_len(&sg[i])));
		if ((i + 1) == *sg_count)
			m_sg->flags |= 1U << mhba->eot_flag;

		sgd_inc(mhba, m_sg);
	}

	return 0;
}
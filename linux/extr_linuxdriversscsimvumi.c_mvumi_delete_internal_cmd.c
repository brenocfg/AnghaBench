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
struct mvumi_sgl {int baseaddr_h; scalar_t__ baseaddr_l; } ;
struct mvumi_hba {unsigned int ib_max_size; int /*<<< orphan*/  pdev; } ;
struct mvumi_cmd {int frame_phys; TYPE_1__* frame; TYPE_1__* data_buf; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * payload; scalar_t__ sg_counts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mvumi_cmd*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,unsigned int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  sgd_getsz (struct mvumi_hba*,struct mvumi_sgl*,unsigned int) ; 

__attribute__((used)) static void mvumi_delete_internal_cmd(struct mvumi_hba *mhba,
						struct mvumi_cmd *cmd)
{
	struct mvumi_sgl *m_sg;
	unsigned int size;
	dma_addr_t phy_addr;

	if (cmd && cmd->frame) {
		if (cmd->frame->sg_counts) {
			m_sg = (struct mvumi_sgl *) &cmd->frame->payload[0];
			sgd_getsz(mhba, m_sg, size);

			phy_addr = (dma_addr_t) m_sg->baseaddr_l |
				(dma_addr_t) ((m_sg->baseaddr_h << 16) << 16);

			pci_free_consistent(mhba->pdev, size, cmd->data_buf,
								phy_addr);
		}
		pci_free_consistent(mhba->pdev, mhba->ib_max_size,
				cmd->frame, cmd->frame_phys);
		kfree(cmd);
	}
}
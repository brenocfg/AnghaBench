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
typedef  int u32 ;
struct hisi_hba {int n_phy; int reject_stp_links_msk; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CON_CONTROL ; 
 int CON_CONTROL_CFG_OPEN_ACC_STP_MSK ; 
 int /*<<< orphan*/  DMA_TX_DFX1 ; 
 int DMA_TX_DFX1_IPTT_MSK ; 
 int /*<<< orphan*/  clear_bit (int,int*) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void phys_try_accept_stp_links_v2_hw(struct hisi_hba *hisi_hba)
{
	int phy_no;
	u32 dma_tx_dfx1;

	for (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) {
		if (!(hisi_hba->reject_stp_links_msk & BIT(phy_no)))
			continue;

		dma_tx_dfx1 = hisi_sas_phy_read32(hisi_hba, phy_no,
						DMA_TX_DFX1);
		if (dma_tx_dfx1 & DMA_TX_DFX1_IPTT_MSK) {
			u32 cfg = hisi_sas_phy_read32(hisi_hba,
				phy_no, CON_CONTROL);

			cfg |= CON_CONTROL_CFG_OPEN_ACC_STP_MSK;
			hisi_sas_phy_write32(hisi_hba, phy_no,
				CON_CONTROL, cfg);
			clear_bit(phy_no, &hisi_hba->reject_stp_links_msk);
		}
	}
}
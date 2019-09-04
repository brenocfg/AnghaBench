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
struct hisi_hba {int reject_stp_links_msk; int n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_CONTROL ; 
 int CON_CONTROL_CFG_OPEN_ACC_STP_MSK ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void phys_reject_stp_links_v2_hw(struct hisi_hba *hisi_hba)
{
	u32 cfg;
	int phy_no;

	hisi_hba->reject_stp_links_msk = (1 << hisi_hba->n_phy) - 1;
	for (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) {
		cfg = hisi_sas_phy_read32(hisi_hba, phy_no, CON_CONTROL);
		if (!(cfg & CON_CONTROL_CFG_OPEN_ACC_STP_MSK))
			continue;

		cfg &= ~CON_CONTROL_CFG_OPEN_ACC_STP_MSK;
		hisi_sas_phy_write32(hisi_hba, phy_no, CON_CONTROL, cfg);
	}
}
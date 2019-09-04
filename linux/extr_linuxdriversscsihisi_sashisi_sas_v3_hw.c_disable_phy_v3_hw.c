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
struct hisi_hba {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  PHY_CFG ; 
 int PHY_CFG_ENA_MSK ; 
 int PHY_CFG_PHY_RST_MSK ; 
 int /*<<< orphan*/  PHY_STATE ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void disable_phy_v3_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	u32 cfg = hisi_sas_phy_read32(hisi_hba, phy_no, PHY_CFG);
	u32 state;

	cfg &= ~PHY_CFG_ENA_MSK;
	hisi_sas_phy_write32(hisi_hba, phy_no, PHY_CFG, cfg);

	mdelay(50);

	state = hisi_sas_read32(hisi_hba, PHY_STATE);
	if (state & BIT(phy_no)) {
		cfg |= PHY_CFG_PHY_RST_MSK;
		hisi_sas_phy_write32(hisi_hba, phy_no, PHY_CFG, cfg);
	}
}
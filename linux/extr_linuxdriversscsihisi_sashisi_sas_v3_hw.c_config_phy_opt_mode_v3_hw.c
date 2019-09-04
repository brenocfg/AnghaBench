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
 int /*<<< orphan*/  PHY_CFG ; 
 int PHY_CFG_DC_OPT_MSK ; 
 int PHY_CFG_DC_OPT_OFF ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void config_phy_opt_mode_v3_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	u32 cfg = hisi_sas_phy_read32(hisi_hba, phy_no, PHY_CFG);

	cfg &= ~PHY_CFG_DC_OPT_MSK;
	cfg |= 1 << PHY_CFG_DC_OPT_OFF;
	hisi_sas_phy_write32(hisi_hba, phy_no, PHY_CFG, cfg);
}
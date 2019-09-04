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
struct phy_dm_struct {int support_ic_type; scalar_t__* enable_adaptivity; scalar_t__* enable_antdiv; } ;

/* Variables and functions */
 int ODM_BB_ADAPTIVITY ; 
 int ODM_BB_ANT_DIV ; 
 int ODM_BB_CCK_PD ; 
 int ODM_BB_CFO_TRACKING ; 
 int ODM_BB_DIG ; 
 int ODM_BB_FA_CNT ; 
 int ODM_BB_RATE_ADAPTIVE ; 
 int ODM_BB_RA_MASK ; 
 int ODM_BB_RSSI_MONITOR ; 
 int /*<<< orphan*/  ODM_CMNINFO_ABILITY ; 
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int ODM_RF_TX_PWR_TRACK ; 
 int ODM_RTL8821C ; 
#define  ODM_RTL8822B 128 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  odm_cmn_info_init (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void phydm_supportability_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 support_ability = 0;

	if (dm->support_ic_type != ODM_RTL8821C)
		return;

	switch (dm->support_ic_type) {
	/*---------------AC Series-------------------*/

	case ODM_RTL8822B:
		support_ability |= ODM_BB_DIG | ODM_BB_FA_CNT | ODM_BB_CCK_PD |
				   ODM_BB_CFO_TRACKING | ODM_BB_RATE_ADAPTIVE |
				   ODM_BB_RSSI_MONITOR | ODM_BB_RA_MASK |
				   ODM_RF_TX_PWR_TRACK;
		break;

	default:
		support_ability |= ODM_BB_DIG | ODM_BB_FA_CNT | ODM_BB_CCK_PD |
				   ODM_BB_CFO_TRACKING | ODM_BB_RATE_ADAPTIVE |
				   ODM_BB_RSSI_MONITOR | ODM_BB_RA_MASK |
				   ODM_RF_TX_PWR_TRACK;

		ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
			     "[Warning] Supportability Init Warning !!!\n");
		break;
	}

	if (*dm->enable_antdiv)
		support_ability |= ODM_BB_ANT_DIV;

	if (*dm->enable_adaptivity) {
		ODM_RT_TRACE(dm, ODM_COMP_INIT,
			     "ODM adaptivity is set to Enabled!!!\n");

		support_ability |= ODM_BB_ADAPTIVITY;

	} else {
		ODM_RT_TRACE(dm, ODM_COMP_INIT,
			     "ODM adaptivity is set to disnabled!!!\n");
		/**/
	}

	ODM_RT_TRACE(dm, ODM_COMP_INIT, "PHYDM support_ability = ((0x%x))\n",
		     support_ability);
	odm_cmn_info_init(dm, ODM_CMNINFO_ABILITY, support_ability);
}
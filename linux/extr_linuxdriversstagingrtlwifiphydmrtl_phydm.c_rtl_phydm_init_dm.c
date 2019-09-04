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
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int ODM_BB_CCK_PD ; 
 int ODM_BB_CFO_TRACKING ; 
 int ODM_BB_DIG ; 
 int ODM_BB_DYNAMIC_TXPWR ; 
 int ODM_BB_FA_CNT ; 
 int ODM_BB_NHM_CNT ; 
 int ODM_BB_RA_MASK ; 
 int ODM_BB_RSSI_MONITOR ; 
 int /*<<< orphan*/  ODM_CMNINFO_ABILITY ; 
 int ODM_MAC_EDCA_TURBO ; 
 int ODM_RF_CALIBRATION ; 
 int ODM_RF_TX_PWR_TRACK ; 
 int /*<<< orphan*/  odm_cmn_info_update (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_dm_init (struct phy_dm_struct*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static int rtl_phydm_init_dm(struct rtl_priv *rtlpriv)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	u32 support_ability = 0;

	/* clang-format off */
	support_ability = 0
			| ODM_BB_DIG
			| ODM_BB_RA_MASK
			| ODM_BB_DYNAMIC_TXPWR
			| ODM_BB_FA_CNT
			| ODM_BB_RSSI_MONITOR
			| ODM_BB_CCK_PD
	/*		| ODM_BB_PWR_SAVE*/
			| ODM_BB_CFO_TRACKING
			| ODM_MAC_EDCA_TURBO
			| ODM_RF_TX_PWR_TRACK
			| ODM_RF_CALIBRATION
			| ODM_BB_NHM_CNT
	/*		| ODM_BB_PWR_TRAIN*/
			;
	/* clang-format on */

	odm_cmn_info_update(dm, ODM_CMNINFO_ABILITY, support_ability);

	odm_dm_init(dm);

	return 0;
}
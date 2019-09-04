#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct rtl_ps_ctl {int /*<<< orphan*/  dot11_psmode; } ;
struct TYPE_8__ {int /*<<< orphan*/  antenna_test; int /*<<< orphan*/  forced_igi_lb; int /*<<< orphan*/  forced_data_rate; int /*<<< orphan*/  adaptivity_en; } ;
struct TYPE_7__ {int /*<<< orphan*/  rxbytesunicast_inperiod_tp; int /*<<< orphan*/  txbytesunicast_inperiod_tp; int /*<<< orphan*/  rxbytesunicast; int /*<<< orphan*/  txbytesunicast; } ;
struct rtl_phy {scalar_t__ rf_type; int /*<<< orphan*/  current_channel; int /*<<< orphan*/  current_chan_bw; } ;
struct rtl_priv {TYPE_4__ phydm; TYPE_3__ stats; TYPE_2__* cfg; struct rtl_phy phy; } ;
struct rtl_phydm_params {int mp_chip; int efuse0x3d7; int efuse0x3d8; int fab_ver; int cut_ver; } ;
struct rtl_mac {int /*<<< orphan*/  act_scanning; int /*<<< orphan*/  cur_40_prime_sc; } ;
struct rtl_hal {int oem_id; scalar_t__ external_lna_2g; scalar_t__ external_lna_5g; scalar_t__ external_pa_2g; scalar_t__ external_pa_5g; int type_gpa; int type_apa; int type_glna; int type_alna; int rfe_type; int /*<<< orphan*/  current_bandtype; } ;
struct rtl_efuse {int antenna_div_type; int /*<<< orphan*/  antenna_div_cfg; } ;
struct phy_dm_struct {void* adapter; } ;
typedef  enum odm_ic_type { ____Placeholder_odm_ic_type } odm_ic_type ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {scalar_t__ (* get_btc_status ) () ;} ;

/* Variables and functions */
 int ODM_1T1R ; 
 int ODM_1T2R ; 
 int ODM_2T2R ; 
 int ODM_2T2R_GREEN ; 
 int ODM_2T3R ; 
 int ODM_2T4R ; 
 int ODM_3T3R ; 
 int ODM_3T4R ; 
 int ODM_4T4R ; 
 int ODM_ASSOCIATE_ENTRY_NUM ; 
 int ODM_BOARD_BT ; 
 int ODM_BOARD_DEFAULT ; 
 int ODM_BOARD_EXT_LNA ; 
 int ODM_BOARD_EXT_LNA_5G ; 
 int ODM_BOARD_EXT_PA ; 
 int ODM_BOARD_EXT_PA_5G ; 
 int ODM_CE ; 
 int /*<<< orphan*/  ODM_CMNINFO_5G_EXT_LNA ; 
 int /*<<< orphan*/  ODM_CMNINFO_5G_EXT_PA ; 
 int /*<<< orphan*/  ODM_CMNINFO_ABILITY ; 
 int /*<<< orphan*/  ODM_CMNINFO_ADAPTIVITY ; 
 int /*<<< orphan*/  ODM_CMNINFO_ALNA ; 
 int /*<<< orphan*/  ODM_CMNINFO_ANT_DIV ; 
 int /*<<< orphan*/  ODM_CMNINFO_ANT_TEST ; 
 int /*<<< orphan*/  ODM_CMNINFO_APA ; 
 int /*<<< orphan*/  ODM_CMNINFO_BAND ; 
 int /*<<< orphan*/  ODM_CMNINFO_BE_FIX_TX_ANT ; 
 int /*<<< orphan*/  ODM_CMNINFO_BOARD_TYPE ; 
 int /*<<< orphan*/  ODM_CMNINFO_BW ; 
 int /*<<< orphan*/  ODM_CMNINFO_BWIFI_TEST ; 
 int /*<<< orphan*/  ODM_CMNINFO_CHNL ; 
 int /*<<< orphan*/  ODM_CMNINFO_CUT_VER ; 
 int /*<<< orphan*/  ODM_CMNINFO_EFUSE0X3D7 ; 
 int /*<<< orphan*/  ODM_CMNINFO_EFUSE0X3D8 ; 
 int /*<<< orphan*/  ODM_CMNINFO_EXT_LNA ; 
 int /*<<< orphan*/  ODM_CMNINFO_EXT_PA ; 
 int /*<<< orphan*/  ODM_CMNINFO_EXT_TRSW ; 
 int /*<<< orphan*/  ODM_CMNINFO_FAB_VER ; 
 int /*<<< orphan*/  ODM_CMNINFO_FORCED_IGI_LB ; 
 int /*<<< orphan*/  ODM_CMNINFO_FORCED_RATE ; 
 int /*<<< orphan*/  ODM_CMNINFO_GLNA ; 
 int /*<<< orphan*/  ODM_CMNINFO_GPA ; 
 int /*<<< orphan*/  ODM_CMNINFO_IC_TYPE ; 
 int /*<<< orphan*/  ODM_CMNINFO_INTERFACE ; 
 int /*<<< orphan*/  ODM_CMNINFO_IQKFWOFFLOAD ; 
 int /*<<< orphan*/  ODM_CMNINFO_MP_TEST_CHIP ; 
 int /*<<< orphan*/  ODM_CMNINFO_PATCH_ID ; 
 int /*<<< orphan*/  ODM_CMNINFO_PLATFORM ; 
 int /*<<< orphan*/  ODM_CMNINFO_POWER_SAVING ; 
 int /*<<< orphan*/  ODM_CMNINFO_REGRFKFREEENABLE ; 
 int /*<<< orphan*/  ODM_CMNINFO_RFE_TYPE ; 
 int /*<<< orphan*/  ODM_CMNINFO_RFKFREEENABLE ; 
 int /*<<< orphan*/  ODM_CMNINFO_RF_ANTENNA_TYPE ; 
 int /*<<< orphan*/  ODM_CMNINFO_RF_TYPE ; 
 int /*<<< orphan*/  ODM_CMNINFO_RX_TP ; 
 int /*<<< orphan*/  ODM_CMNINFO_RX_UNI ; 
 int /*<<< orphan*/  ODM_CMNINFO_SCAN ; 
 int /*<<< orphan*/  ODM_CMNINFO_SEC_CHNL_OFFSET ; 
 int /*<<< orphan*/  ODM_CMNINFO_STA_STATUS ; 
 int /*<<< orphan*/  ODM_CMNINFO_TX_TP ; 
 int /*<<< orphan*/  ODM_CMNINFO_TX_UNI ; 
 int /*<<< orphan*/  ODM_CMNINFO_WITH_EXT_ANTENNA_SWITCH ; 
 int ODM_ITRF_PCIE ; 
 int ODM_RF_CALIBRATION ; 
 int ODM_RF_TX_PWR_TRACK ; 
 int ODM_XTXR ; 
 int /*<<< orphan*/  PHYDM_ADAPINFO_CARRIER_SENSE_ENABLE ; 
 int /*<<< orphan*/  PHYDM_ADAPINFO_DCBACKOFF ; 
 int /*<<< orphan*/  PHYDM_ADAPINFO_DYNAMICLINKADAPTIVITY ; 
 int /*<<< orphan*/  PHYDM_ADAPINFO_TH_EDCCA_HL_DIFF ; 
 int /*<<< orphan*/  PHYDM_ADAPINFO_TH_L2H_INI ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T2R ; 
 scalar_t__ RF_2T2R_GREEN ; 
 scalar_t__ RF_2T3R ; 
 scalar_t__ RF_2T4R ; 
 scalar_t__ RF_3T3R ; 
 scalar_t__ RF_3T4R ; 
 scalar_t__ RF_4T4R ; 
 int /*<<< orphan*/  odm_cmn_info_hook (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  odm_cmn_info_init (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_cmn_info_ptr_array_hook (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  odm_cmn_info_update (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydm_adaptivity_info_init (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydm_init_debug_setting (struct phy_dm_struct*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 
 scalar_t__ stub1 () ; 

__attribute__((used)) static int _rtl_phydm_init_com_info(struct rtl_priv *rtlpriv,
				    enum odm_ic_type ic_type,
				    struct rtl_phydm_params *params)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	u8 odm_board_type = ODM_BOARD_DEFAULT;
	u32 support_ability;
	int i;

	dm->adapter = (void *)rtlpriv;

	odm_cmn_info_init(dm, ODM_CMNINFO_PLATFORM, ODM_CE);

	odm_cmn_info_init(dm, ODM_CMNINFO_IC_TYPE, ic_type);

	odm_cmn_info_init(dm, ODM_CMNINFO_INTERFACE, ODM_ITRF_PCIE);

	odm_cmn_info_init(dm, ODM_CMNINFO_MP_TEST_CHIP, params->mp_chip);

	odm_cmn_info_init(dm, ODM_CMNINFO_PATCH_ID, rtlhal->oem_id);

	odm_cmn_info_init(dm, ODM_CMNINFO_BWIFI_TEST, 1);

	if (rtlphy->rf_type == RF_1T1R)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_1T1R);
	else if (rtlphy->rf_type == RF_1T2R)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_1T2R);
	else if (rtlphy->rf_type == RF_2T2R)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_2T2R);
	else if (rtlphy->rf_type == RF_2T2R_GREEN)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_2T2R_GREEN);
	else if (rtlphy->rf_type == RF_2T3R)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_2T3R);
	else if (rtlphy->rf_type == RF_2T4R)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_2T4R);
	else if (rtlphy->rf_type == RF_3T3R)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_3T3R);
	else if (rtlphy->rf_type == RF_3T4R)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_3T4R);
	else if (rtlphy->rf_type == RF_4T4R)
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_4T4R);
	else
		odm_cmn_info_init(dm, ODM_CMNINFO_RF_TYPE, ODM_XTXR);

	/* 1 ======= BoardType: ODM_CMNINFO_BOARD_TYPE ======= */
	if (rtlhal->external_lna_2g != 0) {
		odm_board_type |= ODM_BOARD_EXT_LNA;
		odm_cmn_info_init(dm, ODM_CMNINFO_EXT_LNA, 1);
	}
	if (rtlhal->external_lna_5g != 0) {
		odm_board_type |= ODM_BOARD_EXT_LNA_5G;
		odm_cmn_info_init(dm, ODM_CMNINFO_5G_EXT_LNA, 1);
	}
	if (rtlhal->external_pa_2g != 0) {
		odm_board_type |= ODM_BOARD_EXT_PA;
		odm_cmn_info_init(dm, ODM_CMNINFO_EXT_PA, 1);
	}
	if (rtlhal->external_pa_5g != 0) {
		odm_board_type |= ODM_BOARD_EXT_PA_5G;
		odm_cmn_info_init(dm, ODM_CMNINFO_5G_EXT_PA, 1);
	}
	if (rtlpriv->cfg->ops->get_btc_status())
		odm_board_type |= ODM_BOARD_BT;

	odm_cmn_info_init(dm, ODM_CMNINFO_BOARD_TYPE, odm_board_type);
	/* 1 ============== End of BoardType ============== */

	odm_cmn_info_init(dm, ODM_CMNINFO_GPA, rtlhal->type_gpa);
	odm_cmn_info_init(dm, ODM_CMNINFO_APA, rtlhal->type_apa);
	odm_cmn_info_init(dm, ODM_CMNINFO_GLNA, rtlhal->type_glna);
	odm_cmn_info_init(dm, ODM_CMNINFO_ALNA, rtlhal->type_alna);

	odm_cmn_info_init(dm, ODM_CMNINFO_RFE_TYPE, rtlhal->rfe_type);

	odm_cmn_info_init(dm, ODM_CMNINFO_EXT_TRSW, 0);

	/*Add by YuChen for kfree init*/
	odm_cmn_info_init(dm, ODM_CMNINFO_REGRFKFREEENABLE, 2);
	odm_cmn_info_init(dm, ODM_CMNINFO_RFKFREEENABLE, 0);

	/*Antenna diversity relative parameters*/
	odm_cmn_info_hook(dm, ODM_CMNINFO_ANT_DIV,
			  &rtlefuse->antenna_div_cfg);
	odm_cmn_info_init(dm, ODM_CMNINFO_RF_ANTENNA_TYPE,
			  rtlefuse->antenna_div_type);
	odm_cmn_info_init(dm, ODM_CMNINFO_BE_FIX_TX_ANT, 0);
	odm_cmn_info_init(dm, ODM_CMNINFO_WITH_EXT_ANTENNA_SWITCH, 0);

	/* (8822B) efuse 0x3D7 & 0x3D8 for TX PA bias */
	odm_cmn_info_init(dm, ODM_CMNINFO_EFUSE0X3D7, params->efuse0x3d7);
	odm_cmn_info_init(dm, ODM_CMNINFO_EFUSE0X3D8, params->efuse0x3d8);

	/*Add by YuChen for adaptivity init*/
	odm_cmn_info_hook(dm, ODM_CMNINFO_ADAPTIVITY,
			  &rtlpriv->phydm.adaptivity_en);
	phydm_adaptivity_info_init(dm, PHYDM_ADAPINFO_CARRIER_SENSE_ENABLE,
				   false);
	phydm_adaptivity_info_init(dm, PHYDM_ADAPINFO_DCBACKOFF, 0);
	phydm_adaptivity_info_init(dm, PHYDM_ADAPINFO_DYNAMICLINKADAPTIVITY,
				   false);
	phydm_adaptivity_info_init(dm, PHYDM_ADAPINFO_TH_L2H_INI, 0);
	phydm_adaptivity_info_init(dm, PHYDM_ADAPINFO_TH_EDCCA_HL_DIFF, 0);

	odm_cmn_info_init(dm, ODM_CMNINFO_IQKFWOFFLOAD, 0);

	/* Pointer reference */
	odm_cmn_info_hook(dm, ODM_CMNINFO_TX_UNI,
			  &rtlpriv->stats.txbytesunicast);
	odm_cmn_info_hook(dm, ODM_CMNINFO_RX_UNI,
			  &rtlpriv->stats.rxbytesunicast);
	odm_cmn_info_hook(dm, ODM_CMNINFO_BAND, &rtlhal->current_bandtype);
	odm_cmn_info_hook(dm, ODM_CMNINFO_FORCED_RATE,
			  &rtlpriv->phydm.forced_data_rate);
	odm_cmn_info_hook(dm, ODM_CMNINFO_FORCED_IGI_LB,
			  &rtlpriv->phydm.forced_igi_lb);

	odm_cmn_info_hook(dm, ODM_CMNINFO_SEC_CHNL_OFFSET,
			  &mac->cur_40_prime_sc);
	odm_cmn_info_hook(dm, ODM_CMNINFO_BW, &rtlphy->current_chan_bw);
	odm_cmn_info_hook(dm, ODM_CMNINFO_CHNL, &rtlphy->current_channel);

	odm_cmn_info_hook(dm, ODM_CMNINFO_SCAN, &mac->act_scanning);
	odm_cmn_info_hook(dm, ODM_CMNINFO_POWER_SAVING,
			  &ppsc->dot11_psmode); /* may add new boolean flag */
	/*Add by Yuchen for phydm beamforming*/
	odm_cmn_info_hook(dm, ODM_CMNINFO_TX_TP,
			  &rtlpriv->stats.txbytesunicast_inperiod_tp);
	odm_cmn_info_hook(dm, ODM_CMNINFO_RX_TP,
			  &rtlpriv->stats.rxbytesunicast_inperiod_tp);
	odm_cmn_info_hook(dm, ODM_CMNINFO_ANT_TEST,
			  &rtlpriv->phydm.antenna_test);
	for (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++)
		odm_cmn_info_ptr_array_hook(dm, ODM_CMNINFO_STA_STATUS, i,
					    NULL);

	phydm_init_debug_setting(dm);

	odm_cmn_info_init(dm, ODM_CMNINFO_FAB_VER, params->fab_ver);
	odm_cmn_info_init(dm, ODM_CMNINFO_CUT_VER, params->cut_ver);

	/* after ifup, ability is updated again */
	support_ability = ODM_RF_CALIBRATION | ODM_RF_TX_PWR_TRACK;
	odm_cmn_info_update(dm, ODM_CMNINFO_ABILITY, support_ability);

	return 0;
}
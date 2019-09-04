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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int* internal_pa_5g; } ;
struct rtl_hal {scalar_t__ current_bandtype; scalar_t__ macphymode; int interfaceindex; int during_mac1init_radioa; int during_mac0init_radiob; } ;
struct rtl_phy {int num_total_rfpath; } ;
struct rtl_priv {TYPE_1__ efuse; struct rtl_hal rtlhal; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ DUALMAC_DUALPHY ; 
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 int RF90_PATH_A ; 
 int RF90_PATH_B ; 
 int RFREG_OFFSET_MASK ; 
 int RF_CHNL_NUM_5G ; 
 int RF_CHNL_NUM_5G_40M ; 
 int RF_REG_NUM_FOR_C_CUT_2G ; 
 int RF_REG_NUM_FOR_C_CUT_5G ; 
 int RF_REG_NUM_FOR_C_CUT_5G_INTERNALPA ; 
 int RF_SYN_G4 ; 
 int RF_SYN_G7 ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl92d_phy_enable_rf_env (struct ieee80211_hw*,int,int*) ; 
 int /*<<< orphan*/  _rtl92d_phy_restore_rf_env (struct ieee80211_hw*,int,int*) ; 
 int* curveindex_2g ; 
 int* curveindex_5g ; 
 int* rf_chnl_5g ; 
 int* rf_chnl_5g_40m ; 
 int* rf_for_c_cut_5g_internal_pa ; 
 int** rf_pram_c_5g_int_pa ; 
 int* rf_reg_for_c_cut_2g ; 
 int* rf_reg_for_c_cut_5g ; 
 int /*<<< orphan*/ * rf_reg_mask_for_c_cut_2g ; 
 int** rf_reg_param_for_c_cut_2g ; 
 int** rf_reg_pram_c_5g ; 
 int rf_syn_g4_for_c_cut_2g ; 
 int rtl92d_phy_enable_anotherphy (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92d_phy_powerdown_anotherphy (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl_get_rfreg (struct ieee80211_hw*,int,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int,int,int,int) ; 

__attribute__((used)) static void _rtl92d_phy_switch_rf_setting(struct ieee80211_hw *hw, u8 channel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u8 path = rtlhal->current_bandtype ==
	    BAND_ON_5G ? RF90_PATH_A : RF90_PATH_B;
	u8 index = 0, i = 0, rfpath = RF90_PATH_A;
	bool need_pwr_down = false, internal_pa = false;
	u32 u4regvalue, mask = 0x1C000, value = 0, u4tmp, u4tmp2;

	RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD, "====>\n");
	/* config path A for 5G */
	if (rtlhal->current_bandtype == BAND_ON_5G) {
		RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD, "====>5G\n");
		u4tmp = curveindex_5g[channel - 1];
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"ver 1 set RF-A, 5G, 0x28 = 0x%x !!\n", u4tmp);
		for (i = 0; i < RF_CHNL_NUM_5G; i++) {
			if (channel == rf_chnl_5g[i] && channel <= 140)
				index = 0;
		}
		for (i = 0; i < RF_CHNL_NUM_5G_40M; i++) {
			if (channel == rf_chnl_5g_40m[i] && channel <= 140)
				index = 1;
		}
		if (channel == 149 || channel == 155 || channel == 161)
			index = 2;
		else if (channel == 151 || channel == 153 || channel == 163
			 || channel == 165)
			index = 3;
		else if (channel == 157 || channel == 159)
			index = 4;

		if (rtlhal->macphymode == DUALMAC_DUALPHY
		    && rtlhal->interfaceindex == 1) {
			need_pwr_down = rtl92d_phy_enable_anotherphy(hw, false);
			rtlhal->during_mac1init_radioa = true;
			/* asume no this case */
			if (need_pwr_down)
				_rtl92d_phy_enable_rf_env(hw, path,
							  &u4regvalue);
		}
		for (i = 0; i < RF_REG_NUM_FOR_C_CUT_5G; i++) {
			if (i == 0 && (rtlhal->macphymode == DUALMAC_DUALPHY)) {
				rtl_set_rfreg(hw, (enum radio_path)path,
					      rf_reg_for_c_cut_5g[i],
					      RFREG_OFFSET_MASK, 0xE439D);
			} else if (rf_reg_for_c_cut_5g[i] == RF_SYN_G4) {
				u4tmp2 = (rf_reg_pram_c_5g[index][i] &
				     0x7FF) | (u4tmp << 11);
				if (channel == 36)
					u4tmp2 &= ~(BIT(7) | BIT(6));
				rtl_set_rfreg(hw, (enum radio_path)path,
					      rf_reg_for_c_cut_5g[i],
					      RFREG_OFFSET_MASK, u4tmp2);
			} else {
				rtl_set_rfreg(hw, (enum radio_path)path,
					      rf_reg_for_c_cut_5g[i],
					      RFREG_OFFSET_MASK,
					      rf_reg_pram_c_5g[index][i]);
			}
			RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
				 "offset 0x%x value 0x%x path %d index %d readback 0x%x\n",
				 rf_reg_for_c_cut_5g[i],
				 rf_reg_pram_c_5g[index][i],
				 path, index,
				 rtl_get_rfreg(hw, (enum radio_path)path,
					       rf_reg_for_c_cut_5g[i],
					       RFREG_OFFSET_MASK));
		}
		if (need_pwr_down)
			_rtl92d_phy_restore_rf_env(hw, path, &u4regvalue);
		if (rtlhal->during_mac1init_radioa)
			rtl92d_phy_powerdown_anotherphy(hw, false);
		if (channel < 149)
			value = 0x07;
		else if (channel >= 149)
			value = 0x02;
		if (channel >= 36 && channel <= 64)
			index = 0;
		else if (channel >= 100 && channel <= 140)
			index = 1;
		else
			index = 2;
		for (rfpath = RF90_PATH_A; rfpath < rtlphy->num_total_rfpath;
			rfpath++) {
			if (rtlhal->macphymode == DUALMAC_DUALPHY &&
				rtlhal->interfaceindex == 1)	/* MAC 1 5G */
				internal_pa = rtlpriv->efuse.internal_pa_5g[1];
			else
				internal_pa =
					 rtlpriv->efuse.internal_pa_5g[rfpath];
			if (internal_pa) {
				for (i = 0;
				     i < RF_REG_NUM_FOR_C_CUT_5G_INTERNALPA;
				     i++) {
					rtl_set_rfreg(hw, rfpath,
						rf_for_c_cut_5g_internal_pa[i],
						RFREG_OFFSET_MASK,
						rf_pram_c_5g_int_pa[index][i]);
					RT_TRACE(rtlpriv, COMP_RF, DBG_LOUD,
						 "offset 0x%x value 0x%x path %d index %d\n",
						 rf_for_c_cut_5g_internal_pa[i],
						 rf_pram_c_5g_int_pa[index][i],
						 rfpath, index);
				}
			} else {
				rtl_set_rfreg(hw, (enum radio_path)rfpath, 0x0B,
					      mask, value);
			}
		}
	} else if (rtlhal->current_bandtype == BAND_ON_2_4G) {
		RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD, "====>2.4G\n");
		u4tmp = curveindex_2g[channel - 1];
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"ver 3 set RF-B, 2G, 0x28 = 0x%x !!\n", u4tmp);
		if (channel == 1 || channel == 2 || channel == 4 || channel == 9
		    || channel == 10 || channel == 11 || channel == 12)
			index = 0;
		else if (channel == 3 || channel == 13 || channel == 14)
			index = 1;
		else if (channel >= 5 && channel <= 8)
			index = 2;
		if (rtlhal->macphymode == DUALMAC_DUALPHY) {
			path = RF90_PATH_A;
			if (rtlhal->interfaceindex == 0) {
				need_pwr_down =
					 rtl92d_phy_enable_anotherphy(hw, true);
				rtlhal->during_mac0init_radiob = true;

				if (need_pwr_down)
					_rtl92d_phy_enable_rf_env(hw, path,
								  &u4regvalue);
			}
		}
		for (i = 0; i < RF_REG_NUM_FOR_C_CUT_2G; i++) {
			if (rf_reg_for_c_cut_2g[i] == RF_SYN_G7)
				rtl_set_rfreg(hw, (enum radio_path)path,
					rf_reg_for_c_cut_2g[i],
					RFREG_OFFSET_MASK,
					(rf_reg_param_for_c_cut_2g[index][i] |
					BIT(17)));
			else
				rtl_set_rfreg(hw, (enum radio_path)path,
					      rf_reg_for_c_cut_2g[i],
					      RFREG_OFFSET_MASK,
					      rf_reg_param_for_c_cut_2g
					      [index][i]);
			RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
				 "offset 0x%x value 0x%x mak 0x%x path %d index %d readback 0x%x\n",
				 rf_reg_for_c_cut_2g[i],
				 rf_reg_param_for_c_cut_2g[index][i],
				 rf_reg_mask_for_c_cut_2g[i], path, index,
				 rtl_get_rfreg(hw, (enum radio_path)path,
					       rf_reg_for_c_cut_2g[i],
					       RFREG_OFFSET_MASK));
		}
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"cosa ver 3 set RF-B, 2G, 0x28 = 0x%x !!\n",
			rf_syn_g4_for_c_cut_2g | (u4tmp << 11));

		rtl_set_rfreg(hw, (enum radio_path)path, RF_SYN_G4,
			      RFREG_OFFSET_MASK,
			      rf_syn_g4_for_c_cut_2g | (u4tmp << 11));
		if (need_pwr_down)
			_rtl92d_phy_restore_rf_env(hw, path, &u4regvalue);
		if (rtlhal->during_mac0init_radiob)
			rtl92d_phy_powerdown_anotherphy(hw, true);
	}
	RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD, "<====\n");
}
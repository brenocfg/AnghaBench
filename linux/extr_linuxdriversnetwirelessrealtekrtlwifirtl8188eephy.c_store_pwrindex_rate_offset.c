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
typedef  scalar_t__ u32 ;
struct rtl_phy {int pwrgroup_cnt; scalar_t__** mcs_txpwrlevel_origoffset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RTXAGC_A_CCK1_MCS32 ; 
 scalar_t__ RTXAGC_A_MCS03_MCS00 ; 
 scalar_t__ RTXAGC_A_MCS07_MCS04 ; 
 scalar_t__ RTXAGC_A_MCS11_MCS08 ; 
 scalar_t__ RTXAGC_A_MCS15_MCS12 ; 
 scalar_t__ RTXAGC_A_RATE18_06 ; 
 scalar_t__ RTXAGC_A_RATE54_24 ; 
 scalar_t__ RTXAGC_B_CCK11_A_CCK2_11 ; 
 scalar_t__ RTXAGC_B_CCK1_55_MCS32 ; 
 scalar_t__ RTXAGC_B_MCS03_MCS00 ; 
 scalar_t__ RTXAGC_B_MCS07_MCS04 ; 
 scalar_t__ RTXAGC_B_MCS11_MCS08 ; 
 scalar_t__ RTXAGC_B_MCS15_MCS12 ; 
 scalar_t__ RTXAGC_B_RATE18_06 ; 
 scalar_t__ RTXAGC_B_RATE54_24 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 scalar_t__ get_rf_type (struct rtl_phy*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void store_pwrindex_rate_offset(struct ieee80211_hw *hw,
				       u32 regaddr, u32 bitmask,
				       u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	int count = rtlphy->pwrgroup_cnt;

	if (regaddr == RTXAGC_A_RATE18_06) {
		rtlphy->mcs_txpwrlevel_origoffset[count][0] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][0] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][0]);
	}
	if (regaddr == RTXAGC_A_RATE54_24) {
		rtlphy->mcs_txpwrlevel_origoffset[count][1] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][1] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][1]);
	}
	if (regaddr == RTXAGC_A_CCK1_MCS32) {
		rtlphy->mcs_txpwrlevel_origoffset[count][6] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][6] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][6]);
	}
	if (regaddr == RTXAGC_B_CCK11_A_CCK2_11 && bitmask == 0xffffff00) {
		rtlphy->mcs_txpwrlevel_origoffset[count][7] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][7] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][7]);
	}
	if (regaddr == RTXAGC_A_MCS03_MCS00) {
		rtlphy->mcs_txpwrlevel_origoffset[count][2] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][2] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][2]);
	}
	if (regaddr == RTXAGC_A_MCS07_MCS04) {
		rtlphy->mcs_txpwrlevel_origoffset[count][3] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][3] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][3]);
	}
	if (regaddr == RTXAGC_A_MCS11_MCS08) {
		rtlphy->mcs_txpwrlevel_origoffset[count][4] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][4] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][4]);
	}
	if (regaddr == RTXAGC_A_MCS15_MCS12) {
		rtlphy->mcs_txpwrlevel_origoffset[count][5] = data;
		if (get_rf_type(rtlphy) == RF_1T1R) {
			count++;
			rtlphy->pwrgroup_cnt = count;
		}
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][5] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][5]);
	}
	if (regaddr == RTXAGC_B_RATE18_06) {
		rtlphy->mcs_txpwrlevel_origoffset[count][8] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][8] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][8]);
	}
	if (regaddr == RTXAGC_B_RATE54_24) {
		rtlphy->mcs_txpwrlevel_origoffset[count][9] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][9] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][9]);
	}
	if (regaddr == RTXAGC_B_CCK1_55_MCS32) {
		rtlphy->mcs_txpwrlevel_origoffset[count][14] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][14] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][14]);
	}
	if (regaddr == RTXAGC_B_CCK11_A_CCK2_11 && bitmask == 0x000000ff) {
		rtlphy->mcs_txpwrlevel_origoffset[count][15] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][15] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][15]);
	}
	if (regaddr == RTXAGC_B_MCS03_MCS00) {
		rtlphy->mcs_txpwrlevel_origoffset[count][10] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][10] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][10]);
	}
	if (regaddr == RTXAGC_B_MCS07_MCS04) {
		rtlphy->mcs_txpwrlevel_origoffset[count][11] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][11] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][11]);
	}
	if (regaddr == RTXAGC_B_MCS11_MCS08) {
		rtlphy->mcs_txpwrlevel_origoffset[count][12] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][12] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][12]);
	}
	if (regaddr == RTXAGC_B_MCS15_MCS12) {
		rtlphy->mcs_txpwrlevel_origoffset[count][13] = data;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "MCSTxPowerLevelOriginalOffset[%d][13] = 0x%x\n",
			  count,
			  rtlphy->mcs_txpwrlevel_origoffset[count][13]);
		if (get_rf_type(rtlphy) != RF_1T1R) {
			count++;
			rtlphy->pwrgroup_cnt = count;
		}
	}
}
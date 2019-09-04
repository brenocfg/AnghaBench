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
typedef  int u8 ;
struct rtl_phy {int rf_pathmap; scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFPGA0_TXINFO ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T2R ; 
 scalar_t__ RF_2T2R_GREEN ; 
 int /*<<< orphan*/  ROFDM0_TRXPATHENABLE ; 
 int _rtl92s_phy_bb_config_parafile (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_phy_init_register_definition (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,...) ; 
 scalar_t__ rtl92s_phy_query_bb_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool rtl92s_phy_bb_config(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	bool rtstatus = true;
	u8 pathmap, index, rf_num = 0;
	u8 path1, path2;

	_rtl92s_phy_init_register_definition(hw);

	/* Config BB and AGC */
	rtstatus = _rtl92s_phy_bb_config_parafile(hw);


	/* Check BB/RF confiuration setting. */
	/* We only need to configure RF which is turned on. */
	path1 = (u8)(rtl92s_phy_query_bb_reg(hw, RFPGA0_TXINFO, 0xf));
	mdelay(10);
	path2 = (u8)(rtl92s_phy_query_bb_reg(hw, ROFDM0_TRXPATHENABLE, 0xf));
	pathmap = path1 | path2;

	rtlphy->rf_pathmap = pathmap;
	for (index = 0; index < 4; index++) {
		if ((pathmap >> index) & 0x1)
			rf_num++;
	}

	if ((rtlphy->rf_type == RF_1T1R && rf_num != 1) ||
	    (rtlphy->rf_type == RF_1T2R && rf_num != 2) ||
	    (rtlphy->rf_type == RF_2T2R && rf_num != 2) ||
	    (rtlphy->rf_type == RF_2T2R_GREEN && rf_num != 2)) {
		pr_err("RF_Type(%x) does not match RF_Num(%x)!!\n",
		       rtlphy->rf_type, rf_num);
		pr_err("path1 0x%x, path2 0x%x, pathmap 0x%x\n",
		       path1, path2, pathmap);
	}

	return rtstatus;
}
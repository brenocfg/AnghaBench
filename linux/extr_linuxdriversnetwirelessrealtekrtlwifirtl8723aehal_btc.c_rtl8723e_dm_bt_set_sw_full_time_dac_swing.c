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
typedef  int u32 ;
struct TYPE_2__ {int sw_coexist_all_off; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtl8723_phy_set_bb_reg (struct ieee80211_hw*,int,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_set_sw_full_time_dac_swing(
		struct ieee80211_hw *hw,
		bool sw_dac_swing_on,
		u32 sw_dac_swing_lvl)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (sw_dac_swing_on) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "[BTCoex], SwDacSwing = 0x%x\n", sw_dac_swing_lvl);
		rtl8723_phy_set_bb_reg(hw, 0x880, 0xff000000,
				       sw_dac_swing_lvl);
		rtlpriv->btcoexist.sw_coexist_all_off = false;
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "[BTCoex], SwDacSwing Off!\n");
		rtl8723_phy_set_bb_reg(hw, 0x880, 0xff000000, 0xc0);
	}
}
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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rtl8723e_fill_h2c_cmd (struct ieee80211_hw*,int,int,int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_set_fw_wlan_act(struct ieee80211_hw *hw,
					   u8 wlan_act_hi, u8 wlan_act_lo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter_hi[1] = {0};
	u8 h2c_parameter_lo[1] = {0};
	h2c_parameter_hi[0] = wlan_act_hi;
	h2c_parameter_lo[0] = wlan_act_lo;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], Set WLAN_ACT Hi:Lo=0x%x/0x%x\n",
		wlan_act_hi, wlan_act_lo);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], write 0x22=0x%x\n", h2c_parameter_hi[0]);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], write 0x11=0x%x\n", h2c_parameter_lo[0]);

	/* WLAN_ACT = High duration, unit:ms */
	rtl8723e_fill_h2c_cmd(hw, 0x22, 1, h2c_parameter_hi);
	/*  WLAN_ACT = Low duration, unit:3*625us */
	rtl8723e_fill_h2c_cmd(hw, 0x11, 1, h2c_parameter_lo);
}
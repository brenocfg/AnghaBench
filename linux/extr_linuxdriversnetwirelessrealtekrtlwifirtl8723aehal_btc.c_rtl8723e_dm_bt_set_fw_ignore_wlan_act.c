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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int fw_coexist_all_off; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtl8723e_fill_h2c_cmd (struct ieee80211_hw*,int,int,int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_set_fw_ignore_wlan_act(struct ieee80211_hw *hw,
						  bool b_enable)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = {0};

	if (b_enable) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], BT Ignore Wlan_Act !!\n");
		h2c_parameter[0] |= BIT(0);		/* function enable */
		rtlpriv->btcoexist.fw_coexist_all_off = false;
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], BT don't ignore Wlan_Act !!\n");
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		 "[BTCoex], set FW for BT Ignore Wlan_Act, write 0x25=0x%x\n",
		 h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x25, 1, h2c_parameter);
}
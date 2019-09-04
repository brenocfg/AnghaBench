#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int lps_counter; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int high_priority_tx; int high_priority_rx; int low_priority_tx; int low_priority_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int MASKHWORD ; 
 int MASKLWORD ; 
 int REG_HIGH_PRIORITY_TXRX ; 
 int REG_LOW_PRIORITY_TXRX ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 TYPE_2__ hal_coex_8723 ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int) ; 

__attribute__((used)) static void rtl8723e_dm_bt_bt_hw_counters_monitor(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 reg_hp_tx_rx, reg_lp_tx_rx, u32_tmp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;

	reg_hp_tx_rx = REG_HIGH_PRIORITY_TXRX;
	reg_lp_tx_rx = REG_LOW_PRIORITY_TXRX;

	u32_tmp = rtl_read_dword(rtlpriv, reg_hp_tx_rx);
	reg_hp_tx = u32_tmp & MASKLWORD;
	reg_hp_rx = (u32_tmp & MASKHWORD)>>16;

	u32_tmp = rtl_read_dword(rtlpriv, reg_lp_tx_rx);
	reg_lp_tx = u32_tmp & MASKLWORD;
	reg_lp_rx = (u32_tmp & MASKHWORD)>>16;

	if (rtlpriv->btcoexist.lps_counter > 1) {
		reg_hp_tx %= rtlpriv->btcoexist.lps_counter;
		reg_hp_rx %= rtlpriv->btcoexist.lps_counter;
		reg_lp_tx %= rtlpriv->btcoexist.lps_counter;
		reg_lp_rx %= rtlpriv->btcoexist.lps_counter;
	}

	hal_coex_8723.high_priority_tx = reg_hp_tx;
	hal_coex_8723.high_priority_rx = reg_hp_rx;
	hal_coex_8723.low_priority_tx = reg_lp_tx;
	hal_coex_8723.low_priority_rx = reg_lp_rx;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"High Priority Tx/Rx (reg 0x%x)=%x(%d)/%x(%d)\n",
		reg_hp_tx_rx, reg_hp_tx, reg_hp_tx, reg_hp_rx, reg_hp_rx);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"Low Priority Tx/Rx (reg 0x%x)=%x(%d)/%x(%d)\n",
		reg_lp_tx_rx, reg_lp_tx, reg_lp_tx, reg_lp_rx, reg_lp_rx);
	rtlpriv->btcoexist.lps_counter = 0;
	/* rtl_write_byte(rtlpriv, 0x76e, 0xc); */
}
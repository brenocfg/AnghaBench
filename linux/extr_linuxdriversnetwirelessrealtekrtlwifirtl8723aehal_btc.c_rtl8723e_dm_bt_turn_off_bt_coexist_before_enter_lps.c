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
struct rtl_ps_ctl {scalar_t__ inactiveps; } ;
struct TYPE_2__ {scalar_t__ previous_state_h; scalar_t__ cstate_h; scalar_t__ previous_state; scalar_t__ cstate; int /*<<< orphan*/  bt_coexistence; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8723e_btdm_coex_all_off (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

void rtl8723e_dm_bt_turn_off_bt_coexist_before_enter_lps(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	if (!rtlpriv->btcoexist.bt_coexistence)
		return;

	if (ppsc->inactiveps) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BT][DM], Before enter IPS, turn off all Coexist DM\n");
		rtlpriv->btcoexist.cstate = 0;
		rtlpriv->btcoexist.previous_state = 0;
		rtlpriv->btcoexist.cstate_h = 0;
		rtlpriv->btcoexist.previous_state_h = 0;
		rtl8723e_btdm_coex_all_off(hw);
	}
}
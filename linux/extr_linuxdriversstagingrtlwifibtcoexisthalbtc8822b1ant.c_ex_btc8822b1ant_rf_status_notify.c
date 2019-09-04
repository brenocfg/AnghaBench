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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int stop_coex_dm; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 scalar_t__ BTC_RF_OFF ; 
 scalar_t__ BTC_RF_ON ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_WLAN_OFF ; 
 int /*<<< orphan*/  BT_8822B_1ANT_SCOREBOARD_ACTIVE ; 
 int /*<<< orphan*/  BT_8822B_1ANT_SCOREBOARD_ONOFF ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ignore_wlan_act (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ex_btc8822b1ant_rf_status_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], RF Status notify\n");

	if (type == BTC_RF_ON) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], RF is turned ON!!\n");
		btcoexist->stop_coex_dm = false;

		halbtc8822b1ant_post_state_to_bt(
			btcoexist, BT_8822B_1ANT_SCOREBOARD_ACTIVE, true);
		halbtc8822b1ant_post_state_to_bt(
			btcoexist, BT_8822B_1ANT_SCOREBOARD_ONOFF, true);

	} else if (type == BTC_RF_OFF) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], RF is turned OFF!!\n");

		halbtc8822b1ant_post_state_to_bt(
			btcoexist, BT_8822B_1ANT_SCOREBOARD_ACTIVE, false);
		halbtc8822b1ant_post_state_to_bt(
			btcoexist, BT_8822B_1ANT_SCOREBOARD_ONOFF, false);
		halbtc8822b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 0);

		halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_1ANT_PHASE_WLAN_OFF);
		/* for test : s3 bt disppear , fail rate 1/600*/

		halbtc8822b1ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);

		btcoexist->stop_coex_dm = true;
	}
}
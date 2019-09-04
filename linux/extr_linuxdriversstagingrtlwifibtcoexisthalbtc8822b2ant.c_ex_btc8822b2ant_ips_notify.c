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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int under_ips; int under_lps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 scalar_t__ BTC_IPS_ENTER ; 
 scalar_t__ BTC_IPS_LEAVE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_WLAN_OFF ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_ACTIVE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_ONOFF ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_coex_all_off (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_init_coex_dm (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_init_hw_config (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_query_bt_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ex_btc8822b2ant_ips_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	if (type == BTC_IPS_ENTER) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;
		coex_sta->under_lps = false;

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, false);

		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_WLAN_OFF);

		halbtc8822b2ant_action_coex_all_off(btcoexist);
	} else if (type == BTC_IPS_LEAVE) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, true);
		halbtc8822b2ant_init_hw_config(btcoexist, false);
		halbtc8822b2ant_init_coex_dm(btcoexist);
		halbtc8822b2ant_query_bt_info(btcoexist);
	}
}
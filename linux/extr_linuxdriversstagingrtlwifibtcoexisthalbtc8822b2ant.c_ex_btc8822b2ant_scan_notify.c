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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int wifi_is_high_pri_task; int scan_ap_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 scalar_t__ BTC_SCAN_FINISH ; 
 scalar_t__ BTC_SCAN_START ; 
 scalar_t__ BTC_SCAN_START_2G ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_ACTIVE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_SCAN ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_query_bt_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_run_coexist_mechanism (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8822b2ant_scan_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false;
	bool wifi_under_5g = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], SCAN notify()\n");

	halbtc8822b2ant_post_state_to_bt(btcoexist,
					 BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	/* this can't be removed for RF off_on event, or BT would dis-connect */
	halbtc8822b2ant_query_bt_info(btcoexist);

	if (type == BTC_SCAN_START) {
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G,
				   &wifi_under_5g);

		if (wifi_under_5g) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** SCAN START notify (5g)\n");

			halbtc8822b2ant_action_wifi_under5g(btcoexist);
			return;
		}

		coex_sta->wifi_is_high_pri_task = true;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ********** SCAN START notify (2g)\n");

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);

		return;
	}

	if (type == BTC_SCAN_START_2G) {
		if (!wifi_connected)
			coex_sta->wifi_is_high_pri_task = true;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], SCAN START notify (2G)\n");

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_SCAN, true);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);

		halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_2ANT_PHASE_2G_RUNTIME);

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);

	} else if (type == BTC_SCAN_FINISH) {
		coex_sta->wifi_is_high_pri_task = false;

		btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
				   &coex_sta->scan_ap_num);

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], SCAN FINISH notify  (Scan-AP = %d)\n",
			 coex_sta->scan_ap_num);

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_SCAN, false);

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);
	}
}
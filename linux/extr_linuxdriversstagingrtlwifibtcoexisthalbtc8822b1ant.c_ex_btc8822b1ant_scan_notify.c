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
struct TYPE_2__ {int freeze_coexrun_by_btinfo; int wifi_is_high_pri_task; int scan_ap_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 scalar_t__ BTC_SCAN_START ; 
 scalar_t__ BTC_SCAN_START_2G ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_connected_scan (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_not_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_not_connected_scan (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_query_bt_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8822b1ant_scan_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false;
	bool wifi_under_5g = false;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	coex_sta->freeze_coexrun_by_btinfo = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	if (wifi_connected)
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ********** WL connected before SCAN\n");
	else
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], **********  WL is not connected before SCAN\n");

	halbtc8822b1ant_query_bt_info(btcoexist);

	/*2.4 g 1*/
	if (type == BTC_SCAN_START) {
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G,
				   &wifi_under_5g);
		/*5 g 1*/

		if (wifi_under_5g) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** (scan_notify_5g_scan_start) **********\n");
			halbtc8822b1ant_action_wifi_under5g(btcoexist);
			return;
		}

		/* 2.4G.2.3*/
		coex_sta->wifi_is_high_pri_task = true;

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ********** (scan_notify_2g_scan_start) **********\n");

		if (!wifi_connected) { /* non-connected scan */
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** wifi is not connected scan **********\n");
			halbtc8822b1ant_action_wifi_not_connected_scan(
				btcoexist);
		} else { /* wifi is connected */
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** wifi is connected scan **********\n");
			halbtc8822b1ant_action_wifi_connected_scan(btcoexist);
		}

		return;
	}

	if (type == BTC_SCAN_START_2G) {
		coex_sta->wifi_is_high_pri_task = true;

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ********** (scan_notify_2g_sacn_start_for_switch_band_used) **********\n");

		if (!wifi_connected) { /* non-connected scan */
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** wifi is not connected **********\n");

			halbtc8822b1ant_action_wifi_not_connected_scan(
				btcoexist);
		} else { /* wifi is connected */
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** wifi is connected **********\n");
			halbtc8822b1ant_action_wifi_connected_scan(btcoexist);
		}
	} else {
		coex_sta->wifi_is_high_pri_task = false;

		/* 2.4G 5 WL scan finish, then get and update sacn ap numbers */
		/*5 g 4*/
		btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
				   &coex_sta->scan_ap_num);

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ********** (scan_finish_notify) **********\n");

		if (!wifi_connected) { /* non-connected scan */
			halbtc8822b1ant_action_wifi_not_connected(btcoexist);
		} else {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** scan_finish_notify wifi is connected **********\n");
			halbtc8822b1ant_action_wifi_connected(btcoexist);
		}
	}
}
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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int (* btc_read_4byte ) (struct btc_coexist*,int) ;scalar_t__ (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int wifi_is_high_pri_task; int scan_ap_num; scalar_t__ c2h_bt_inquiry_page; scalar_t__ bt_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_PTA ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_LINK_STATUS ; 
 scalar_t__ BTC_SCAN_FINISH ; 
 scalar_t__ BTC_SCAN_START ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8723b1ant_action_wifi_conn_scan (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8723b1ant_action_wifi_not_conn (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8723b1ant_action_wifi_not_conn_scan (struct btc_coexist*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_bt_inquiry (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_wifi_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_wifi_multiport (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  halbtc8723b1ant_limited_tx (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_query_bt_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (struct btc_coexist*,int) ; 
 scalar_t__ stub2 (struct btc_coexist*,int) ; 
 scalar_t__ stub3 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8723b1ant_scan_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false, bt_hs_on = false;
	u8 u8tmpa, u8tmpb;
	u32 u32tmp;
	u32 wifi_link_status = 0;
	u32 num_of_wifi_link = 0;
	bool bt_ctrl_agg_buf_size = false;
	u8 agg_buf_size = 5;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	if (type == BTC_SCAN_START) {
		coex_sta->wifi_is_high_pri_task = true;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], SCAN START notify\n");
		/* Force antenna setup for no scan result issue */
		halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     FORCE_EXEC, false, false);
		u32tmp = btcoexist->btc_read_4byte(btcoexist, 0x948);
		u8tmpa = btcoexist->btc_read_1byte(btcoexist, 0x765);
		u8tmpb = btcoexist->btc_read_1byte(btcoexist, 0x67);

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], 0x948=0x%x, 0x765=0x%x, 0x67=0x%x\n",
			 u32tmp, u8tmpa, u8tmpb);
	} else {
		coex_sta->wifi_is_high_pri_task = false;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], SCAN FINISH notify\n");

		btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
				   &coex_sta->scan_ap_num);
	}

	if (coex_sta->bt_disabled)
		return;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	halbtc8723b1ant_query_bt_info(btcoexist);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wifi_link_status);
	num_of_wifi_link = wifi_link_status >> 16;
	if (num_of_wifi_link >= 2) {
		halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					   bt_ctrl_agg_buf_size, agg_buf_size);
		halbtc8723b1ant_action_wifi_multiport(btcoexist);
		return;
	}

	if (coex_sta->c2h_bt_inquiry_page) {
		halbtc8723b1ant_action_bt_inquiry(btcoexist);
		return;
	} else if (bt_hs_on) {
		halbtc8723b1ant_action_hs(btcoexist);
		return;
	}

	if (BTC_SCAN_START == type) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], SCAN START notify\n");
		if (!wifi_connected)
			/* non-connected scan */
			btc8723b1ant_action_wifi_not_conn_scan(btcoexist);
		else
			/* wifi is connected */
			btc8723b1ant_action_wifi_conn_scan(btcoexist);
	} else if (BTC_SCAN_FINISH == type) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], SCAN FINISH notify\n");
		if (!wifi_connected)
			/* non-connected scan */
			btc8723b1ant_action_wifi_not_conn(btcoexist);
		else
			halbtc8723b1ant_action_wifi_connected(btcoexist);
	}
}
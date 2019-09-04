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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ arp_cnt; } ;
struct TYPE_3__ {int wifi_is_high_pri_task; scalar_t__ c2h_bt_inquiry_page; scalar_t__ bt_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_PTA ; 
 scalar_t__ BTC_ASSOCIATE_FINISH ; 
 scalar_t__ BTC_ASSOCIATE_START ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_LINK_STATUS ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8723b1ant_act_wifi_not_conn_asso_auth (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8723b1ant_action_wifi_not_conn (struct btc_coexist*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_bt_inquiry (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_wifi_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_wifi_multiport (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  halbtc8723b1ant_limited_tx (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8723b1ant_connect_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false, bt_hs_on = false;
	u32 wifi_link_status = 0;
	u32 num_of_wifi_link = 0;
	bool bt_ctrl_agg_buf_size = false, under_4way = false;
	u8 agg_buf_size = 5;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	if (btcoexist->manual_control || btcoexist->stop_coex_dm ||
	    coex_sta->bt_disabled)
		return;

	if (type == BTC_ASSOCIATE_START) {
		coex_sta->wifi_is_high_pri_task = true;

		/* Force antenna setup for no scan result issue */
		halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     FORCE_EXEC, false, false);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CONNECT START notify\n");
		coex_dm->arp_cnt = 0;
	} else {
		coex_sta->wifi_is_high_pri_task = false;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CONNECT FINISH notify\n");
	}

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wifi_link_status);
	num_of_wifi_link = wifi_link_status>>16;
	if (num_of_wifi_link >= 2) {
		halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					   bt_ctrl_agg_buf_size, agg_buf_size);
		halbtc8723b1ant_action_wifi_multiport(btcoexist);
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	if (coex_sta->c2h_bt_inquiry_page) {
		halbtc8723b1ant_action_bt_inquiry(btcoexist);
		return;
	} else if (bt_hs_on) {
		halbtc8723b1ant_action_hs(btcoexist);
		return;
	}

	if (BTC_ASSOCIATE_START == type) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CONNECT START notify\n");
		btc8723b1ant_act_wifi_not_conn_asso_auth(btcoexist);
	} else if (BTC_ASSOCIATE_FINISH == type) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CONNECT FINISH notify\n");

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
				   &wifi_connected);
		if (!wifi_connected)
			/* non-connected scan */
			btc8723b1ant_action_wifi_not_conn(btcoexist);
		else
			halbtc8723b1ant_action_wifi_connected(btcoexist);
	}
}
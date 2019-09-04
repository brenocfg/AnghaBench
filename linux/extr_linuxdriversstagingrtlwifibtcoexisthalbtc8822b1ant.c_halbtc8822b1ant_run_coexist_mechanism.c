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
struct btc_bt_link_info {scalar_t__ sco_exist; scalar_t__ bt_link_exist; scalar_t__ a2dp_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ bt_status; } ;
struct TYPE_3__ {scalar_t__ c2h_bt_inquiry_page; scalar_t__ is_setup_link; scalar_t__ bt_disabled; scalar_t__ bt_whck_test; scalar_t__ freeze_coexrun_by_btinfo; int /*<<< orphan*/  run_time_state; scalar_t__ under_lps; scalar_t__ under_ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_U1_IOT_PEER ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_LINK_STATUS ; 
 scalar_t__ BTC_IOT_PEER_CISCO ; 
 scalar_t__ BTC_IOT_PEER_UNKNOWN ; 
 int /*<<< orphan*/  BTC_SET_BL_INC_SCAN_DEV_NUM ; 
 int /*<<< orphan*/  BTC_SET_BL_MIRACAST_PLUS_BT ; 
 int BTC_WIFI_BW_HT40 ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_SCO_BUSY ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int WIFI_P2P_GO_CONNECTED ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_bt_inquiry (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_bt_relink (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_bt_whck_test (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_multi_port (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_native_lps (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_not_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_not_connected_asso_auth (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_not_connected_scan (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_only (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_limited_tx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_run_sw_coexist_mechanism (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b1ant_sw_mechanism (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8822b1ant_run_coexist_mechanism(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_connected = false, bt_hs_on = false;
	bool increase_scan_dev_num = false;
	bool bt_ctrl_agg_buf_size = false;
	bool miracast_plus_bt = false;
	u8 agg_buf_size = 5;
	u32 wifi_link_status = 0;
	u32 num_of_wifi_link = 0, wifi_bw;
	u8 iot_peer = BTC_IOT_PEER_UNKNOWN;
	bool wifi_under_5g = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], RunCoexistMechanism()===>\n");

	if (btcoexist->manual_control) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for Manual CTRL <===\n");
		return;
	}

	if (btcoexist->stop_coex_dm) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for Stop Coex DM <===\n");
		return;
	}

	if (coex_sta->under_ips) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], wifi is under IPS !!!\n");
		return;
	}

	if ((coex_sta->under_lps) &&
	    (coex_dm->bt_status != BT_8822B_1ANT_BT_STATUS_ACL_BUSY)) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), wifi is under LPS !!!\n");
		halbtc8822b1ant_action_wifi_native_lps(btcoexist);
		return;
	}

	if (!coex_sta->run_time_state) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], return for run_time_state = false !!!\n");
		return;
	}

	if (coex_sta->freeze_coexrun_by_btinfo) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), return for freeze_coexrun_by_btinfo\n");
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);
	if (wifi_under_5g) {
		halbtc8822b1ant_action_wifi_under5g(btcoexist);

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], WiFi is under 5G!!!\n");
		return;
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], WiFi is under 2G!!!\n");

	halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_1ANT_PHASE_2G_RUNTIME);

	if (coex_sta->bt_whck_test) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is under WHCK TEST!!!\n");
		halbtc8822b1ant_action_bt_whck_test(btcoexist);
		return;
	}

	if (coex_sta->bt_disabled) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is disabled !!!\n");
		halbtc8822b1ant_action_wifi_only(btcoexist);
		return;
	}

	if (coex_sta->is_setup_link) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is re-link !!!\n");
		halbtc8822b1ant_action_bt_relink(btcoexist);
		return;
	}

	if ((coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_ACL_BUSY) ||
	    (coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_SCO_BUSY) ||
	    (coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY))
		increase_scan_dev_num = true;

	btcoexist->btc_set(btcoexist, BTC_SET_BL_INC_SCAN_DEV_NUM,
			   &increase_scan_dev_num);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wifi_link_status);
	num_of_wifi_link = wifi_link_status >> 16;

	if ((num_of_wifi_link >= 2) ||
	    (wifi_link_status & WIFI_P2P_GO_CONNECTED)) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"############# [BTCoex],  Multi-Port num_of_wifi_link = %d, wifi_link_status = 0x%x\n",
			num_of_wifi_link, wifi_link_status);

		if (bt_link_info->bt_link_exist) {
			halbtc8822b1ant_limited_tx(btcoexist, NORMAL_EXEC, 1, 1,
						   0, 1);
			miracast_plus_bt = true;
		} else {
			halbtc8822b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0,
						   0, 0);
			miracast_plus_bt = false;
		}
		btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
				   &miracast_plus_bt);
		halbtc8822b1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					   bt_ctrl_agg_buf_size, agg_buf_size);

		if ((bt_link_info->a2dp_exist) &&
		    (coex_sta->c2h_bt_inquiry_page)) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "############# [BTCoex],  BT Is Inquirying\n");
			halbtc8822b1ant_action_bt_inquiry(btcoexist);
		} else {
			halbtc8822b1ant_action_wifi_multi_port(btcoexist);
		}

		return;
	}

	miracast_plus_bt = false;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
			   &miracast_plus_bt);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);

	if ((bt_link_info->bt_link_exist) && (wifi_connected)) {
		halbtc8822b1ant_limited_tx(btcoexist, NORMAL_EXEC, 1, 1, 0, 1);

		btcoexist->btc_get(btcoexist, BTC_GET_U1_IOT_PEER, &iot_peer);

		if (iot_peer != BTC_IOT_PEER_CISCO) {
			if (bt_link_info->sco_exist)
				halbtc8822b1ant_limited_rx(btcoexist,
							   NORMAL_EXEC, true,
							   false, 0x5);
			else
				halbtc8822b1ant_limited_rx(btcoexist,
							   NORMAL_EXEC, false,
							   false, 0x5);
		} else {
			if (bt_link_info->sco_exist) {
				halbtc8822b1ant_limited_rx(btcoexist,
							   NORMAL_EXEC, true,
							   false, 0x5);
			} else {
				if (wifi_bw == BTC_WIFI_BW_HT40)
					halbtc8822b1ant_limited_rx(
						btcoexist, NORMAL_EXEC, false,
						true, 0x10);
				else
					halbtc8822b1ant_limited_rx(
						btcoexist, NORMAL_EXEC, false,
						true, 0x8);
			}
		}

		halbtc8822b1ant_sw_mechanism(btcoexist, true);
		halbtc8822b1ant_run_sw_coexist_mechanism(
			btcoexist); /* just print debug message */
	} else {
		halbtc8822b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);

		halbtc8822b1ant_limited_rx(btcoexist, NORMAL_EXEC, false, false,
					   0x5);

		halbtc8822b1ant_sw_mechanism(btcoexist, false);
		halbtc8822b1ant_run_sw_coexist_mechanism(
			btcoexist); /* just print debug message */
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	if (coex_sta->c2h_bt_inquiry_page) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "############# [BTCoex],  BT Is Inquirying\n");
		halbtc8822b1ant_action_bt_inquiry(btcoexist);
		return;
	} else if (bt_hs_on) {
		halbtc8822b1ant_action_hs(btcoexist);
		return;
	}

	if (!wifi_connected) {
		bool scan = false, link = false, roam = false;

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], wifi is non connected-idle !!!\n");

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

		if (scan)
			halbtc8822b1ant_action_wifi_not_connected_scan(
				btcoexist);
		else if (link || roam)
			halbtc8822b1ant_action_wifi_not_connected_asso_auth(
				btcoexist);
		else
			halbtc8822b1ant_action_wifi_not_connected(btcoexist);
	} else { /* wifi LPS/Busy */
		halbtc8822b1ant_action_wifi_connected(btcoexist);
	}
}
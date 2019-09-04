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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {scalar_t__ bt_link_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ bt_status; int /*<<< orphan*/  cur_algorithm; } ;
struct TYPE_3__ {scalar_t__ switch_band_notify_to; scalar_t__ is_setup_link; scalar_t__ c2h_bt_inquiry_page; scalar_t__ bt_disabled; scalar_t__ bt_whck_test; scalar_t__ freeze_coexrun_by_btinfo; int /*<<< orphan*/  run_time_state; scalar_t__ under_lps; scalar_t__ under_ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_LINK_STATUS ; 
 int /*<<< orphan*/  BTC_SET_BL_MIRACAST_PLUS_BT ; 
 scalar_t__ BTC_SWITCH_TO_24G ; 
 scalar_t__ BTC_SWITCH_TO_24G_NOFORSCAN ; 
 scalar_t__ BT_8822B_2ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8822B_2ANT_BT_STATUS_CONNECTED_IDLE ; 
 scalar_t__ BT_8822B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int WIFI_P2P_GO_CONNECTED ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_algorithm (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_bt_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_bt_idle (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_bt_inquiry (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_bt_relink (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_bt_whck_test (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_coex_all_off (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_link_process (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_multi_port (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_native_lps (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_nonconnected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8822b2ant_run_coexist_mechanism(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 algorithm = 0;
	u32 num_of_wifi_link = 0;
	u32 wifi_link_status = 0;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool miracast_plus_bt = false;
	bool scan = false, link = false, roam = false, under_4way = false,
	     wifi_connected = false, wifi_under_5g = false, bt_hs_on = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

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
	    (coex_dm->bt_status != BT_8822B_2ANT_BT_STATUS_ACL_BUSY)) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), wifi is under LPS !!!\n");
		halbtc8822b2ant_action_wifi_native_lps(btcoexist);
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

	if ((wifi_under_5g) &&
	    (coex_sta->switch_band_notify_to != BTC_SWITCH_TO_24G) &&
	    (coex_sta->switch_band_notify_to != BTC_SWITCH_TO_24G_NOFORSCAN)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], WiFi is under 5G!!!\n");

		halbtc8822b2ant_action_wifi_under5g(btcoexist);
		return;
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], WiFi is under 2G!!!\n");

	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_2ANT_PHASE_2G_RUNTIME);

	if (coex_sta->bt_whck_test) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is under WHCK TEST!!!\n");
		halbtc8822b2ant_action_bt_whck_test(btcoexist);
		return;
	}

	if (coex_sta->bt_disabled) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is disabled!!!\n");
		halbtc8822b2ant_action_coex_all_off(btcoexist);
		return;
	}

	if (coex_sta->c2h_bt_inquiry_page) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is under inquiry/page scan !!\n");
		halbtc8822b2ant_action_bt_inquiry(btcoexist);
		return;
	}

	if (coex_sta->is_setup_link) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is re-link !!!\n");
		halbtc8822b2ant_action_bt_relink(btcoexist);
		return;
	}

	/* for P2P */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wifi_link_status);
	num_of_wifi_link = wifi_link_status >> 16;

	if ((num_of_wifi_link >= 2) ||
	    (wifi_link_status & WIFI_P2P_GO_CONNECTED)) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"############# [BTCoex],  Multi-Port num_of_wifi_link = %d, wifi_link_status = 0x%x\n",
			num_of_wifi_link, wifi_link_status);

		if (bt_link_info->bt_link_exist)
			miracast_plus_bt = true;
		else
			miracast_plus_bt = false;

		btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
				   &miracast_plus_bt);

		if (scan || link || roam || under_4way) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], scan = %d, link = %d, roam = %d 4way = %d!!!\n",
				scan, link, roam, under_4way);

			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], wifi is under linkscan process + Multi-Port !!\n");

			halbtc8822b2ant_action_wifi_link_process(btcoexist);
		} else {
			halbtc8822b2ant_action_wifi_multi_port(btcoexist);
		}

		return;
	}

	miracast_plus_bt = false;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
			   &miracast_plus_bt);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	if (bt_hs_on) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "############# [BTCoex],  BT Is hs\n");
		halbtc8822b2ant_action_bt_hs(btcoexist);
		return;
	}

	if ((BT_8822B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
	     coex_dm->bt_status) ||
	    (coex_dm->bt_status == BT_8822B_2ANT_BT_STATUS_CONNECTED_IDLE)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, bt idle!!.\n");

		halbtc8822b2ant_action_bt_idle(btcoexist);
		return;
	}

	algorithm = halbtc8822b2ant_action_algorithm(btcoexist);
	coex_dm->cur_algorithm = algorithm;
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Algorithm = %d\n", coex_dm->cur_algorithm);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	if (scan || link || roam || under_4way) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], WiFi is under Link Process !!\n");
		halbtc8822b2ant_action_wifi_link_process(btcoexist);
	} else if (wifi_connected) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, wifi connected!!.\n");
		halbtc8822b2ant_action_wifi_connected(btcoexist);

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, wifi not-connected!!.\n");
		halbtc8822b2ant_action_wifi_nonconnected(btcoexist);
	}
}
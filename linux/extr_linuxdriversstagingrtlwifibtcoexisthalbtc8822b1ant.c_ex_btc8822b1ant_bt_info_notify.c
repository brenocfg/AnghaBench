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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int (* btc_get_ble_scan_type_from_bt ) (struct btc_coexist*) ;int /*<<< orphan*/  (* btc_get_ble_scan_para_from_bt ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  stop_coex_dm; int /*<<< orphan*/  manual_control; struct rtl_priv* adapter; } ;
struct TYPE_4__ {int** bt_info_c2h; int bt_info; int bt_info_ext; int bt_info_ext2; int bt_whck_test; int bt_create_connection; int bt_rssi; int c2h_bt_remote_name_req; int is_A2DP_3M; int acl_busy; int voice_over_HOGP; int c2h_bt_inquiry_page; int a2dp_bit_pool; int is_bt_a2dp_sink; int bt_retry_cnt; int is_autoslot; int forbidden_slot; int hid_busy_num; int hid_pair_cnt; int is_setup_link; int bt_relink_downcount; int is_bt_multi_link; int bt_ble_scan_type; int /*<<< orphan*/ * bt_ble_scan_para; scalar_t__ wifi_is_high_pri_task; int /*<<< orphan*/  cnt_page; int /*<<< orphan*/  cnt_role_switch; int /*<<< orphan*/  cnt_ign_wlan_act; int /*<<< orphan*/  cnt_setup_link; int /*<<< orphan*/  cnt_reinit; int /*<<< orphan*/  cnt_remote_name_req; int /*<<< orphan*/  pop_event_cnt; int /*<<< orphan*/ * bt_info_c2h_cnt; } ;
struct TYPE_3__ {scalar_t__ is_ant_det_running; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_MEDIA_CONNECT ; 
 int /*<<< orphan*/  BTC_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  BT_8822B_1ANT_SCOREBOARD_SCAN ; 
 int BT_INFO_8822B_1ANT_B_INQ_PAGE ; 
 int BT_INFO_SRC_8822B_1ANT_MAX ; 
 int BT_INFO_SRC_8822B_1ANT_WIFI_FW ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_ignore_wlan_act (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_run_coexist_mechanism (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_update_bt_link_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_update_wifi_ch_info (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 TYPE_1__* psd_scan ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int stub6 (struct btc_coexist*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int) ; 

void ex_btc8822b1ant_bt_info_notify(struct btc_coexist *btcoexist, u8 *tmp_buf,
				    u8 length)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 i, rsp_source = 0;
	bool wifi_connected = false;
	bool wifi_scan = false, wifi_link = false, wifi_roam = false,
	     wifi_busy = false;
	static bool is_scoreboard_scan;

	if (psd_scan->is_ant_det_running) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bt_info_notify return for AntDet is running\n");
		return;
	}

	rsp_source = tmp_buf[0] & 0xf;
	if (rsp_source >= BT_INFO_SRC_8822B_1ANT_MAX)
		rsp_source = BT_INFO_SRC_8822B_1ANT_WIFI_FW;
	coex_sta->bt_info_c2h_cnt[rsp_source]++;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Bt_info[%d], len=%d, data=[", rsp_source, length);

	for (i = 0; i < length; i++) {
		coex_sta->bt_info_c2h[rsp_source][i] = tmp_buf[i];

		if (i == length - 1) {
			/* last one */
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "0x%02x]\n", tmp_buf[i]);
		} else {
			/* normal */
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "0x%02x, ",
				 tmp_buf[i]);
		}
	}

	coex_sta->bt_info = coex_sta->bt_info_c2h[rsp_source][1];
	coex_sta->bt_info_ext = coex_sta->bt_info_c2h[rsp_source][4];
	coex_sta->bt_info_ext2 = coex_sta->bt_info_c2h[rsp_source][5];

	if (rsp_source != BT_INFO_SRC_8822B_1ANT_WIFI_FW) {
		/* if 0xff, it means BT is under WHCK test */
		coex_sta->bt_whck_test =
			((coex_sta->bt_info == 0xff) ? true : false);

		coex_sta->bt_create_connection =
			((coex_sta->bt_info_c2h[rsp_source][2] & 0x80) ? true :
									 false);

		/* unit: %, value-100 to translate to unit: dBm */
		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 + 10;

		coex_sta->c2h_bt_remote_name_req =
			((coex_sta->bt_info_c2h[rsp_source][2] & 0x20) ? true :
									 false);

		coex_sta->is_A2DP_3M =
			((coex_sta->bt_info_c2h[rsp_source][2] & 0x10) ? true :
									 false);

		coex_sta->acl_busy =
			((coex_sta->bt_info_c2h[rsp_source][1] & 0x9) ? true :
									false);

		coex_sta->voice_over_HOGP =
			((coex_sta->bt_info_ext & 0x10) ? true : false);

		coex_sta->c2h_bt_inquiry_page =
			((coex_sta->bt_info & BT_INFO_8822B_1ANT_B_INQ_PAGE) ?
				 true :
				 false);

		coex_sta->a2dp_bit_pool =
			(((coex_sta->bt_info_c2h[rsp_source][1] & 0x49) ==
			  0x49) ?
				 (coex_sta->bt_info_c2h[rsp_source][6] & 0x7f) :
				 0);

		coex_sta->is_bt_a2dp_sink =
			(coex_sta->bt_info_c2h[rsp_source][6] & 0x80) ? true :
									false;

		coex_sta->bt_retry_cnt =
			coex_sta->bt_info_c2h[rsp_source][2] & 0xf;

		coex_sta->is_autoslot = coex_sta->bt_info_ext2 & 0x8;

		coex_sta->forbidden_slot = coex_sta->bt_info_ext2 & 0x7;

		coex_sta->hid_busy_num = (coex_sta->bt_info_ext2 & 0x30) >> 4;

		coex_sta->hid_pair_cnt = (coex_sta->bt_info_ext2 & 0xc0) >> 6;
		if (coex_sta->bt_retry_cnt >= 1)
			coex_sta->pop_event_cnt++;

		if (coex_sta->c2h_bt_remote_name_req)
			coex_sta->cnt_remote_name_req++;

		if (coex_sta->bt_info_ext & BIT(1))
			coex_sta->cnt_reinit++;

		if (coex_sta->bt_info_ext & BIT(2)) {
			coex_sta->cnt_setup_link++;
			coex_sta->is_setup_link = true;
			coex_sta->bt_relink_downcount = 2;
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Re-Link start in BT info!!\n");
		} else {
			coex_sta->is_setup_link = false;
			coex_sta->bt_relink_downcount = 0;
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Re-Link stop in BT info!!\n");
		}

		if (coex_sta->bt_info_ext & BIT(3))
			coex_sta->cnt_ign_wlan_act++;

		if (coex_sta->bt_info_ext & BIT(6))
			coex_sta->cnt_role_switch++;

		if (coex_sta->bt_info_ext & BIT(7))
			coex_sta->is_bt_multi_link = true;
		else
			coex_sta->is_bt_multi_link = false;

		if (coex_sta->bt_create_connection) {
			coex_sta->cnt_page++;

			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY,
					   &wifi_busy);

			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN,
					   &wifi_scan);
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK,
					   &wifi_link);
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM,
					   &wifi_roam);

			if ((wifi_link) || (wifi_roam) || (wifi_scan) ||
			    (coex_sta->wifi_is_high_pri_task) || (wifi_busy)) {
				is_scoreboard_scan = true;
				halbtc8822b1ant_post_state_to_bt(
					btcoexist,
					BT_8822B_1ANT_SCOREBOARD_SCAN, true);

			} else {
				halbtc8822b1ant_post_state_to_bt(
					btcoexist,
					BT_8822B_1ANT_SCOREBOARD_SCAN, false);
			}
		} else {
			if (is_scoreboard_scan) {
				halbtc8822b1ant_post_state_to_bt(
					btcoexist,
					BT_8822B_1ANT_SCOREBOARD_SCAN, false);
				is_scoreboard_scan = false;
			}
		}

		/* Here we need to resend some wifi info to BT */
		/* because bt is reset and loss of the info. */

		if ((!btcoexist->manual_control) &&
		    (!btcoexist->stop_coex_dm)) {
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
					   &wifi_connected);

			/*  Re-Init */
			if ((coex_sta->bt_info_ext & BIT(1))) {
				RT_TRACE(
					rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT ext info bit1 check, send wifi BW&Chnl to BT!!\n");
				if (wifi_connected)
					halbtc8822b1ant_update_wifi_ch_info(
						btcoexist, BTC_MEDIA_CONNECT);
				else
					halbtc8822b1ant_update_wifi_ch_info(
						btcoexist,
						BTC_MEDIA_DISCONNECT);
			}

			/*	If Ignore_WLanAct && not SetUp_Link */
			if ((coex_sta->bt_info_ext & BIT(3)) &&
			    (!(coex_sta->bt_info_ext & BIT(2)))) {
				RT_TRACE(
					rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n");
				halbtc8822b1ant_ignore_wlan_act(
					btcoexist, FORCE_EXEC, false);
			}
		}
	}

	if ((coex_sta->bt_info_ext & BIT(5))) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT ext info bit4 check, query BLE Scan type!!\n");
		coex_sta->bt_ble_scan_type =
			btcoexist->btc_get_ble_scan_type_from_bt(btcoexist);

		if ((coex_sta->bt_ble_scan_type & 0x1) == 0x1)
			coex_sta->bt_ble_scan_para[0] =
				btcoexist->btc_get_ble_scan_para_from_bt(
					btcoexist, 0x1);
		if ((coex_sta->bt_ble_scan_type & 0x2) == 0x2)
			coex_sta->bt_ble_scan_para[1] =
				btcoexist->btc_get_ble_scan_para_from_bt(
					btcoexist, 0x2);
		if ((coex_sta->bt_ble_scan_type & 0x4) == 0x4)
			coex_sta->bt_ble_scan_para[2] =
				btcoexist->btc_get_ble_scan_para_from_bt(
					btcoexist, 0x4);
	}

	halbtc8822b1ant_update_bt_link_info(btcoexist);

	halbtc8822b1ant_run_coexist_mechanism(btcoexist);
}
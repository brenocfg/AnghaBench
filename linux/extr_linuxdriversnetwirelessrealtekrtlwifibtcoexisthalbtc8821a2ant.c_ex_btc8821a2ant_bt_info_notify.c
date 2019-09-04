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
struct btc_coexist {int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ manual_control; int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_set_bt_reg ) (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ;struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ bt_status; int limited_dig; } ;
struct TYPE_3__ {int c2h_bt_info_req_sent; int** bt_info_c2h; int bt_retry_cnt; int bt_rssi; int bt_info_ext; int bt_tx_rx_mask; int c2h_bt_inquiry_page; int bt_link_exist; int pan_exist; int a2dp_exist; int hid_exist; int sco_exist; int high_priority_tx; int high_priority_rx; int /*<<< orphan*/ * bt_info_c2h_cnt; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT1 ; 
 int /*<<< orphan*/  BTC_BT_REG_RF ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_MEDIA_CONNECT ; 
 int /*<<< orphan*/  BTC_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_LIMITED_DIG ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_TRAFFIC_BUSY ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_TX_RX_MASK ; 
 scalar_t__ BT_8821A_2ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8821A_2ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8821A_2ANT_BT_STATUS_CON_IDLE ; 
 scalar_t__ BT_8821A_2ANT_BT_STATUS_IDLE ; 
 scalar_t__ BT_8821A_2ANT_BT_STATUS_MAX ; 
 scalar_t__ BT_8821A_2ANT_BT_STATUS_SCO_BUSY ; 
 int BT_INFO_8821A_2ANT_B_A2DP ; 
 int BT_INFO_8821A_2ANT_B_ACL_BUSY ; 
 int BT_INFO_8821A_2ANT_B_CONNECTION ; 
 int BT_INFO_8821A_2ANT_B_FTP ; 
 int BT_INFO_8821A_2ANT_B_HID ; 
 int BT_INFO_8821A_2ANT_B_INQ_PAGE ; 
 int BT_INFO_8821A_2ANT_B_SCO_BUSY ; 
 int BT_INFO_8821A_2ANT_B_SCO_ESCO ; 
 int BT_INFO_SRC_8821A_2ANT_MAX ; 
 int BT_INFO_SRC_8821A_2ANT_WIFI_FW ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8821a2ant_ignore_wlan_act (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a2ant_run_coexist_mechanism (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_update_bt_link_info (struct btc_coexist*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  ex_btc8821a2ant_media_status_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8821a2ant_bt_info_notify(struct btc_coexist *btcoexist,
				    u8 *tmp_buf, u8 length)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 bt_info = 0;
	u8 i, rsp_source = 0;
	bool bt_busy = false, limited_dig = false;
	bool wifi_connected = false, wifi_under_5g = false;

	coex_sta->c2h_bt_info_req_sent = false;
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	rsp_source = tmp_buf[0] & 0xf;
	if (rsp_source >= BT_INFO_SRC_8821A_2ANT_MAX)
		rsp_source = BT_INFO_SRC_8821A_2ANT_WIFI_FW;
	coex_sta->bt_info_c2h_cnt[rsp_source]++;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Bt info[%d], length = %d, hex data = [",
		      rsp_source, length);
	for (i = 0; i < length; i++) {
		coex_sta->bt_info_c2h[rsp_source][i] = tmp_buf[i];
		if (i == 1)
			bt_info = tmp_buf[i];
		if (i == length - 1) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "0x%02x]\n", tmp_buf[i]);
		} else {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "0x%02x, ", tmp_buf[i]);
		}
	}

	if (btcoexist->manual_control) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), return for Manual CTRL<===\n");
		return;
	}

	if (BT_INFO_SRC_8821A_2ANT_WIFI_FW != rsp_source) {
		/* [3:0] */
		coex_sta->bt_retry_cnt =
			coex_sta->bt_info_c2h[rsp_source][2]&0xf;

		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 + 10;

		coex_sta->bt_info_ext = coex_sta->bt_info_c2h[rsp_source][4];

		coex_sta->bt_tx_rx_mask =
			(coex_sta->bt_info_c2h[rsp_source][2] & 0x40);
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TX_RX_MASK,
				   &coex_sta->bt_tx_rx_mask);
		if (coex_sta->bt_tx_rx_mask) {
			/* BT into is responded by BT FW and BT RF REG 0x3C !=
			 * 0x01 => Need to switch BT TRx Mask
			 */
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Switch BT TRx Mask since BT RF REG 0x3C != 0x01\n");
			btcoexist->btc_set_bt_reg(btcoexist, BTC_BT_REG_RF,
						  0x3c, 0x01);
		}

		/* Here we need to resend some wifi info to BT
		 * because bt is reset and loss of the info
		 */
		if ((coex_sta->bt_info_ext & BIT1)) {
			btcoexist->btc_get(btcoexist,
				BTC_GET_BL_WIFI_CONNECTED, &wifi_connected);
			if (wifi_connected) {
				ex_btc8821a2ant_media_status_notify(btcoexist,
					BTC_MEDIA_CONNECT);
			} else {
				ex_btc8821a2ant_media_status_notify(btcoexist,
					BTC_MEDIA_DISCONNECT);
			}

		}

		if (!btcoexist->manual_control && !wifi_under_5g) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], BT ext info = 0x%x!!\n",
				    coex_sta->bt_info_ext);
			if ((coex_sta->bt_info_ext & BIT(3))) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], BT ext info bit3=1, wifi_connected=%d\n",
					 wifi_connected);
				if (wifi_connected) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n");
					btc8821a2ant_ignore_wlan_act(btcoexist,
								     FORCE_EXEC,
								     false);
				}
			} else {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], BT ext info bit3=0, wifi_connected=%d\n",
					 wifi_connected);
				/* BT already NOT ignore Wlan active, do nothing
				 * here.
				 */
				if (!wifi_connected) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						"[BTCoex], BT ext info bit3 check, set BT to ignore Wlan active!!\n");
					btc8821a2ant_ignore_wlan_act(
						btcoexist, FORCE_EXEC, true);
				}
			}
		}
	}

	/* check BIT2 first ==> check if bt is under inquiry or page scan*/
	if (bt_info & BT_INFO_8821A_2ANT_B_INQ_PAGE) {
		coex_sta->c2h_bt_inquiry_page = true;
	} else {
		coex_sta->c2h_bt_inquiry_page = false;
	}
	/* set link exist status */
	if (!(bt_info & BT_INFO_8821A_2ANT_B_CONNECTION)) {
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;
	} else { /* connection exists */
		coex_sta->bt_link_exist = true;
		if (bt_info & BT_INFO_8821A_2ANT_B_FTP)
			coex_sta->pan_exist = true;
		else
			coex_sta->pan_exist = false;
		if (bt_info & BT_INFO_8821A_2ANT_B_A2DP)
			coex_sta->a2dp_exist = true;
		else
			coex_sta->a2dp_exist = false;
		if (bt_info & BT_INFO_8821A_2ANT_B_HID)
			coex_sta->hid_exist = true;
		else
			coex_sta->hid_exist = false;
		if (bt_info & BT_INFO_8821A_2ANT_B_SCO_ESCO)
			coex_sta->sco_exist = true;
		else
			coex_sta->sco_exist = false;

		if ((!coex_sta->hid_exist) &&
		    (!coex_sta->c2h_bt_inquiry_page) &&
		    (!coex_sta->sco_exist)) {
			if (coex_sta->high_priority_tx +
				    coex_sta->high_priority_rx >= 160)
				coex_sta->hid_exist = true;
		}
	}

	btc8821a2ant_update_bt_link_info(btcoexist);

	if (!(bt_info & BT_INFO_8821A_2ANT_B_CONNECTION)) {
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_IDLE;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT Non-Connected idle!!!\n");
	} else if (bt_info == BT_INFO_8821A_2ANT_B_CONNECTION) {
		/* connection exists but no busy */
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_CON_IDLE;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n");
	} else if ((bt_info & BT_INFO_8821A_2ANT_B_SCO_ESCO) ||
		   (bt_info & BT_INFO_8821A_2ANT_B_SCO_BUSY)) {
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_SCO_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT SCO busy!!!\n");
	} else if (bt_info & BT_INFO_8821A_2ANT_B_ACL_BUSY) {
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_ACL_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT ACL busy!!!\n");
	} else {
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_MAX;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT Non-Defined state!!!\n");
	}

	if ((coex_dm->bt_status == BT_8821A_2ANT_BT_STATUS_ACL_BUSY) ||
	    (coex_dm->bt_status == BT_8821A_2ANT_BT_STATUS_SCO_BUSY) ||
	    (coex_dm->bt_status == BT_8821A_2ANT_BT_STATUS_ACL_SCO_BUSY)) {
		bt_busy = true;
		limited_dig = true;
	} else {
		bt_busy = false;
		limited_dig = false;
	}

	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	coex_dm->limited_dig = limited_dig;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_LIMITED_DIG, &limited_dig);

	btc8821a2ant_run_coexist_mechanism(btcoexist);
}
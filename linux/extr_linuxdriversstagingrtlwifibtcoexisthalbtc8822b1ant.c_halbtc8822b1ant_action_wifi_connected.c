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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ bt_status; } ;
struct TYPE_3__ {int high_priority_tx; int high_priority_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_AP_MODE_ENABLE ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_SCO_BUSY ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_bt_sco_hid_only_busy (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_connected_bt_acl_busy (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_connected_scan (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_connected_specific_packet (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b1ant_wifi_rssi_state (struct btc_coexist*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b1ant_action_wifi_connected(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_busy = false, rf4ce_enabled = false;
	bool scan = false, link = false, roam = false;
	bool under_4way = false, ap_enable = false, wifi_under_5g = false;
	u8 wifi_rssi_state;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], CoexForWifiConnect()===>\n");

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (wifi_under_5g) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CoexForWifiConnect(), return for wifi is under 5g<===\n");

		halbtc8822b1ant_action_wifi_under5g(btcoexist);

		return;
	}

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], CoexForWifiConnect(), return for wifi is under 2g<===\n");

	halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_1ANT_PHASE_2G_RUNTIME);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	if (under_4way) {
		halbtc8822b1ant_action_wifi_connected_specific_packet(
			btcoexist);
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CoexForWifiConnect(), return for wifi is under 4way<===\n");
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	if (scan || link || roam) {
		if (scan)
			halbtc8822b1ant_action_wifi_connected_scan(btcoexist);
		else
			halbtc8822b1ant_action_wifi_connected_specific_packet(
				btcoexist);
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CoexForWifiConnect(), return for wifi is under scan<===\n");
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	/* tdma and coex table */
	if (!wifi_busy) {
		if (coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_ACL_BUSY) {
			halbtc8822b1ant_action_wifi_connected_bt_acl_busy(
				btcoexist);
		} else if ((BT_8822B_1ANT_BT_STATUS_SCO_BUSY ==
			    coex_dm->bt_status) ||
			   (BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY ==
			    coex_dm->bt_status)) {
			halbtc8822b1ant_action_bt_sco_hid_only_busy(btcoexist);
		} else {
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false,
						8);

			halbtc8822b1ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				BT_8822B_1ANT_PHASE_2G_RUNTIME);

			if ((coex_sta->high_priority_tx) +
				    (coex_sta->high_priority_rx) <=
			    60)
				/*sy modify case16 -> case17*/
				halbtc8822b1ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 1);
			else
				halbtc8822b1ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 1);
		}
	} else {
		if (coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_ACL_BUSY) {
			halbtc8822b1ant_action_wifi_connected_bt_acl_busy(
				btcoexist);
		} else if ((BT_8822B_1ANT_BT_STATUS_SCO_BUSY ==
			    coex_dm->bt_status) ||
			   (BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY ==
			    coex_dm->bt_status)) {
			halbtc8822b1ant_action_bt_sco_hid_only_busy(btcoexist);
		} else {
			if (rf4ce_enabled) {
				btcoexist->btc_write_1byte_bitmask(
					btcoexist, 0x45e, 0x8, 0x1);

				halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 50);

				halbtc8822b1ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 1);
				return;
			}

			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false,
						8);

			halbtc8822b1ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				BT_8822B_1ANT_PHASE_2G_RUNTIME);

			wifi_rssi_state = halbtc8822b1ant_wifi_rssi_state(
				btcoexist, 1, 2, 25, 0);

			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], ********** before  **********\n");
			if (BT_8822B_1ANT_BT_STATUS_NON_CONNECTED_IDLE ==
			    coex_dm->bt_status) {
				if (rf4ce_enabled) {
					btcoexist->btc_write_1byte_bitmask(
						btcoexist, 0x45e, 0x8, 0x1);

					halbtc8822b1ant_ps_tdma(btcoexist,
								NORMAL_EXEC,
								true, 50);

					halbtc8822b1ant_coex_table_with_type(
						btcoexist, NORMAL_EXEC, 1);
					return;
				}

				halbtc8822b1ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 1);
			} else {
				halbtc8822b1ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 1);
			}
		}
	}
}
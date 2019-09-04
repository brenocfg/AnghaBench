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
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {scalar_t__ a2dp_exist; scalar_t__ pan_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ wifi_is_high_pri_task; scalar_t__ bt_create_connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8822b2ant_action_bt_inquiry(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false;
	bool wifi_scan = false, wifi_link = false, wifi_roam = false;
	bool wifi_busy = false;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &wifi_scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &wifi_link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &wifi_roam);

	if ((coex_sta->bt_create_connection) &&
	    ((wifi_link) || (wifi_roam) || (wifi_scan) || (wifi_busy) ||
	     (coex_sta->wifi_is_high_pri_task))) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi link/roam/Scan/busy/hi-pri-task + BT Inq/Page!!\n");

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);

		if ((bt_link_info->a2dp_exist) && (!bt_link_info->pan_exist))
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						15);
		else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						11);
	} else if ((!wifi_connected) && (!wifi_scan)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi no-link + no-scan + BT Inq/Page!!\n");

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
	} else if (bt_link_info->pan_exist) {
		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);

	} else if (bt_link_info->a2dp_exist) {
		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 8);

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC,
						     10);
	} else {
		if ((wifi_link) || (wifi_roam) || (wifi_scan) || (wifi_busy) ||
		    (coex_sta->wifi_is_high_pri_task))
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						21);
		else
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						23);

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);
	}

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 0xd8);
}
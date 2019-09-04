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
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ bt_create_connection; scalar_t__ wifi_is_high_pri_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_AP_MODE_ENABLE ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_TRAFFIC_BUSY ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b1ant_action_bt_inquiry(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_connected = false, ap_enable = false, wifi_busy = false,
	     bt_busy = false, rf4ce_enabled = false;

	bool wifi_scan = false, link = false, roam = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ********** (bt inquiry) **********\n");
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &wifi_scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], ********** scan = %d,  link =%d, roam = %d**********\n",
		wifi_scan, link, roam);

	if ((link) || (roam) || (coex_sta->wifi_is_high_pri_task)) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ********** (bt inquiry wifi  connect or scan ) **********\n");

		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 1);

		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 6);

	} else if ((wifi_scan) && (coex_sta->bt_create_connection)) {
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 6);

	} else if ((!wifi_connected) && (!wifi_scan)) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ********** (bt inquiry wifi non connect) **********\n");

		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);

		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	} else if ((bt_link_info->a2dp_exist) && (bt_link_info->pan_exist)) {
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	} else if (bt_link_info->a2dp_exist) {
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);

		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);
	} else if (wifi_scan) {
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);

		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	} else if (wifi_busy) {
		/* for BT inquiry/page fail after S4 resume */
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		/*aaaa->55aa for bt connect while wl busy*/
		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC,
						     15);
		if (rf4ce_enabled) {
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x45e,
							   0x8, 0x1);

			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						50);

			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 0);
		}
	} else {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ********** (bt inquiry wifi connect) **********\n");

		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);

		halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     NORMAL_EXEC,
					     BT_8822B_1ANT_PHASE_2G_RUNTIME);

		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	}
}
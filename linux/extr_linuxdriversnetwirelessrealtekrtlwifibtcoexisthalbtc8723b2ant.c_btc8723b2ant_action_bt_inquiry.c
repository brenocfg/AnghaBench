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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ bt_abnormal_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  BTC_SET_ACT_DISABLE_LOW_POWER ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8723b2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8723b2ant_dec_bt_pwr (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8723b2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8723b2ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8723b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8723b2ant_sw_mechanism (struct btc_coexist*,int,int,int,int) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void btc8723b2ant_action_bt_inquiry(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false;
	bool low_pwr_disable = true;
	bool scan = false, link = false, roam = false;

	btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
			   &low_pwr_disable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	btc8723b2ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	if (coex_sta->bt_abnormal_scan) {
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 23);
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);
	} else if (scan || link || roam) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi link process + BT Inq/Page!!\n");
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
	} else if (wifi_connected) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi connected + BT Inq/Page!!\n");
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
	} else {
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
	}
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 6);
	btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	btc8723b2ant_sw_mechanism(btcoexist, false, false, false, false);
}
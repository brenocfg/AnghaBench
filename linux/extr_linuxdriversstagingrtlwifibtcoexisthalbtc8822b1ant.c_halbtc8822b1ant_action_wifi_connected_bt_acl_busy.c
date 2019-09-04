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
typedef  scalar_t__ u32 ;
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {scalar_t__ hid_exist; scalar_t__ pan_exist; scalar_t__ pan_only; scalar_t__ a2dp_exist; scalar_t__ a2dp_only; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int scan_ap_num; scalar_t__ wl_noisy_level; scalar_t__ bt_relink_downcount; scalar_t__ is_bt_a2dp_sink; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_wltoggle_coex_table (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
halbtc8822b1ant_action_wifi_connected_bt_acl_busy(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_busy = false, wifi_turbo = false;
	u32 wifi_bw = 1;

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
			   &coex_sta->scan_ap_num);
	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"############# [BTCoex],  scan_ap_num = %d, wl_noisy_level = %d\n",
		coex_sta->scan_ap_num, coex_sta->wl_noisy_level);

	if ((wifi_busy) && (coex_sta->wl_noisy_level == 0))
		wifi_turbo = true;

	if ((coex_sta->bt_relink_downcount != 0) &&
	    (!bt_link_info->pan_exist) && (wifi_busy)) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"############# [BTCoex],  BT Re-Link + A2DP + WL busy\n");

		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	} else if ((bt_link_info->a2dp_exist) && (coex_sta->is_bt_a2dp_sink)) {
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 12);
		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 6);
	} else if (bt_link_info->a2dp_only) { /* A2DP		 */

		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 7);

		if (wifi_turbo)
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 19);
		else
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
	} else if (((bt_link_info->a2dp_exist) && (bt_link_info->pan_exist)) ||
		   (bt_link_info->hid_exist && bt_link_info->a2dp_exist &&
		    bt_link_info->pan_exist)) {
		/* A2DP+PAN(OPP,FTP), HID+A2DP+PAN(OPP,FTP) */

		if (wifi_busy)
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						13);
		else
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						14);

		if (bt_link_info->hid_exist)
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
		else if (wifi_turbo)
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 19);
		else
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
	} else if (bt_link_info->hid_exist &&
		   bt_link_info->a2dp_exist) { /* HID+A2DP */

		if (wifi_bw == 0) { /* if 11bg mode */
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
			halbtc8822b1ant_set_wltoggle_coex_table(
				btcoexist, NORMAL_EXEC, 1, 0xaa, 0x5a, 0xaa,
				0xaa);
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						49);
		} else {
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
			halbtc8822b1ant_limited_rx(btcoexist, NORMAL_EXEC,
						   false, true, 8);
			halbtc8822b1ant_set_wltoggle_coex_table(
				btcoexist, NORMAL_EXEC, 1, 0xaa, 0x5a, 0xaa,
				0xaa);
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						49);
		}
		/* PAN(OPP,FTP), HID+PAN(OPP,FTP) */

	} else if ((bt_link_info->pan_only) ||
		   (bt_link_info->hid_exist && bt_link_info->pan_exist)) {
		if (!wifi_busy)
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						4);
		else
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						3);

		if (bt_link_info->hid_exist)
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
		else if (wifi_turbo)
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 19);
		else
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
	} else {
		/* BT no-profile busy (0x9) */
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 33);
		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	}
}
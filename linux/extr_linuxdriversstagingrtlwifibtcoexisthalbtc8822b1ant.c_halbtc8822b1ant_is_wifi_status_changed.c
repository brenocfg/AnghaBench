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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {int slave_role; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int bt_disabled; scalar_t__ wl_noisy_level; int under_lps; scalar_t__ hid_busy_num; int is_hid_low_pri_tx_overhead; int is_setup_link; scalar_t__ bt_coex_supported_version; scalar_t__ bt_coex_supported_feature; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_RF4CE_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool
halbtc8822b1ant_is_wifi_status_changed(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static bool pre_wifi_busy, pre_under_4way, pre_bt_hs_on,
		pre_rf4ce_enabled, pre_bt_off, pre_bt_slave,
		pre_hid_low_pri_tx_overhead, pre_wifi_under_lps,
		pre_bt_setup_link;
	static u8 pre_hid_busy_num, pre_wl_noisy_level;
	bool wifi_busy = false, under_4way = false, bt_hs_on = false,
	     rf4ce_enabled = false;
	bool wifi_connected = false;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	if (coex_sta->bt_disabled != pre_bt_off) {
		pre_bt_off = coex_sta->bt_disabled;

		if (coex_sta->bt_disabled)
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], BT is disabled !!\n");
		else
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], BT is enabled !!\n");

		coex_sta->bt_coex_supported_feature = 0;
		coex_sta->bt_coex_supported_version = 0;
		return true;
	}
	btcoexist->btc_get(btcoexist, BTC_GET_BL_RF4CE_CONNECTED,
			   &rf4ce_enabled);

	if (rf4ce_enabled != pre_rf4ce_enabled) {
		pre_rf4ce_enabled = rf4ce_enabled;

		if (rf4ce_enabled)
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], rf4ce is enabled !!\n");
		else
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], rf4ce is disabled !!\n");

		return true;
	}

	if (wifi_connected) {
		if (wifi_busy != pre_wifi_busy) {
			pre_wifi_busy = wifi_busy;
			return true;
		}
		if (under_4way != pre_under_4way) {
			pre_under_4way = under_4way;
			return true;
		}
		if (bt_hs_on != pre_bt_hs_on) {
			pre_bt_hs_on = bt_hs_on;
			return true;
		}
		if (coex_sta->wl_noisy_level != pre_wl_noisy_level) {
			pre_wl_noisy_level = coex_sta->wl_noisy_level;
			return true;
		}
		if (coex_sta->under_lps != pre_wifi_under_lps) {
			pre_wifi_under_lps = coex_sta->under_lps;
			if (coex_sta->under_lps)
				return true;
		}
	}

	if (!coex_sta->bt_disabled) {
		if (coex_sta->hid_busy_num != pre_hid_busy_num) {
			pre_hid_busy_num = coex_sta->hid_busy_num;
			return true;
		}

		if (bt_link_info->slave_role != pre_bt_slave) {
			pre_bt_slave = bt_link_info->slave_role;
			return true;
		}

		if (pre_hid_low_pri_tx_overhead !=
		    coex_sta->is_hid_low_pri_tx_overhead) {
			pre_hid_low_pri_tx_overhead =
				coex_sta->is_hid_low_pri_tx_overhead;
			return true;
		}

		if (pre_bt_setup_link != coex_sta->is_setup_link) {
			pre_bt_setup_link = coex_sta->is_setup_link;
			return true;
		}
	}

	return false;
}
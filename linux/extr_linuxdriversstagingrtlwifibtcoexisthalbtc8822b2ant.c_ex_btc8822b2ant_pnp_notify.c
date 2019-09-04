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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {int under_ips; int under_lps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 scalar_t__ BTC_WIFI_PNP_SLEEP ; 
 scalar_t__ BTC_WIFI_PNP_SLEEP_KEEP_ANT ; 
 scalar_t__ BTC_WIFI_PNP_WAKE_UP ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_5G_RUNTIME ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_WLAN_OFF ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_ACTIVE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_ONOFF ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8822b2ant_pnp_notify(struct btc_coexist *btcoexist, u8 pnp_state)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_under_5g = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Pnp notify\n");

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if ((pnp_state == BTC_WIFI_PNP_SLEEP) ||
	    (pnp_state == BTC_WIFI_PNP_SLEEP_KEEP_ANT)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Pnp notify to SLEEP\n");

		/* Sinda 20150819, workaround for driver skip leave IPS/LPS to
		 * speed up sleep time.
		 * Driver do not leave IPS/LPS when driver is going to sleep,
		 * so BTCoexistence think wifi is still under IPS/LPS.
		 * BT should clear UnderIPS/UnderLPS state to avoid mismatch
		 * state after wakeup.
		 */
		coex_sta->under_ips = false;
		coex_sta->under_lps = false;

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, false);

		if (pnp_state == BTC_WIFI_PNP_SLEEP_KEEP_ANT) {
			if (wifi_under_5g)
				halbtc8822b2ant_set_ant_path(
					btcoexist, BTC_ANT_PATH_AUTO,
					FORCE_EXEC,
					BT_8822B_2ANT_PHASE_5G_RUNTIME);
			else
				halbtc8822b2ant_set_ant_path(
					btcoexist, BTC_ANT_PATH_AUTO,
					FORCE_EXEC,
					BT_8822B_2ANT_PHASE_2G_RUNTIME);
		} else {
			halbtc8822b2ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, FORCE_EXEC,
				BT_8822B_2ANT_PHASE_WLAN_OFF);
		}
	} else if (pnp_state == BTC_WIFI_PNP_WAKE_UP) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Pnp notify to WAKE UP\n");

		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, true);
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_ONOFF, true);
	}
}
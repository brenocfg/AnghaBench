#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int stop_coex_dm; int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 scalar_t__ BTC_WIFI_PNP_SLEEP ; 
 scalar_t__ BTC_WIFI_PNP_SLEEP_KEEP_ANT ; 
 scalar_t__ BTC_WIFI_PNP_WAKE_UP ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_5G_RUNTIME ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_WLAN_OFF ; 
 int BT_8822B_1ANT_SCOREBOARD_ACTIVE ; 
 int BT_8822B_1ANT_SCOREBOARD_ONOFF ; 
 int BT_8822B_1ANT_SCOREBOARD_SCAN ; 
 int BT_8822B_1ANT_SCOREBOARD_UNDERTEST ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_post_state_to_bt (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8822b1ant_pnp_notify(struct btc_coexist *btcoexist, u8 pnp_state)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_under_5g = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Pnp notify\n");

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if ((pnp_state == BTC_WIFI_PNP_SLEEP) ||
	    (pnp_state == BTC_WIFI_PNP_SLEEP_KEEP_ANT)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Pnp notify to SLEEP\n");

		halbtc8822b1ant_post_state_to_bt(
			btcoexist, BT_8822B_1ANT_SCOREBOARD_ACTIVE |
					   BT_8822B_1ANT_SCOREBOARD_ONOFF |
					   BT_8822B_1ANT_SCOREBOARD_SCAN |
					   BT_8822B_1ANT_SCOREBOARD_UNDERTEST,
			false);

		if (pnp_state == BTC_WIFI_PNP_SLEEP_KEEP_ANT) {
			if (wifi_under_5g)
				halbtc8822b1ant_set_ant_path(
					btcoexist, BTC_ANT_PATH_AUTO,
					FORCE_EXEC,
					BT_8822B_1ANT_PHASE_5G_RUNTIME);
			else
				halbtc8822b1ant_set_ant_path(
					btcoexist, BTC_ANT_PATH_AUTO,
					FORCE_EXEC,
					BT_8822B_1ANT_PHASE_2G_RUNTIME);
		} else {
			halbtc8822b1ant_set_ant_path(
				btcoexist, BTC_ANT_PATH_AUTO, FORCE_EXEC,
				BT_8822B_1ANT_PHASE_WLAN_OFF);
		}

		btcoexist->stop_coex_dm = true;
	} else if (pnp_state == BTC_WIFI_PNP_WAKE_UP) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Pnp notify to WAKE UP\n");
		btcoexist->stop_coex_dm = false;
	}
}
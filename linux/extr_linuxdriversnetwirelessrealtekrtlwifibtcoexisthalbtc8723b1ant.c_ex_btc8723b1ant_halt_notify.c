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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int stop_coex_dm; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_BT ; 
 int /*<<< orphan*/  BTC_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ex_btc8723b1ant_media_status_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ignore_wlan_act (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void ex_btc8723b1ant_halt_notify(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Halt notify\n");

	btcoexist->stop_coex_dm = true;

	halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT, FORCE_EXEC,
				     false, true);

	halbtc8723b1ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);

	halbtc8723b1ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);
	halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 0);

	ex_btc8723b1ant_media_status_notify(btcoexist, BTC_MEDIA_DISCONNECT);

	btcoexist->stop_coex_dm = true;
}
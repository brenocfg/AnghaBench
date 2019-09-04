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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int under_ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_BT ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 scalar_t__ BTC_IPS_ENTER ; 
 scalar_t__ BTC_IPS_LEAVE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8821a1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a1ant_coex_under_5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_init_coex_dm (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_init_hw_config (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a1ant_query_bt_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8821a1ant_ips_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_under_5g = false;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);
	if (wifi_under_5g) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		return;
	}

	if (BTC_IPS_ENTER == type) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;
		btc8821a1ant_set_ant_path(btcoexist,
					  BTC_ANT_PATH_BT, false, true);
		/* set PTA control */
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
		btc8821a1ant_coex_table_with_type(btcoexist,
						  NORMAL_EXEC, 0);
	} else if (BTC_IPS_LEAVE == type) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;

		btc8821a1ant_init_hw_config(btcoexist, false, false);
		btc8821a1ant_init_coex_dm(btcoexist);
		btc8821a1ant_query_bt_info(btcoexist);
	}
}
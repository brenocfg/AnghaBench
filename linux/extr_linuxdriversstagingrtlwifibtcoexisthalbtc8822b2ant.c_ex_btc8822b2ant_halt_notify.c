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
struct btc_coexist {struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_WLAN_OFF ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_ACTIVE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_ONOFF ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ex_btc8822b2ant_media_status_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ex_btc8822b2ant_halt_notify(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Halt notify\n");

	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, FORCE_EXEC,
				     BT_8822B_2ANT_PHASE_WLAN_OFF);

	ex_btc8822b2ant_media_status_notify(btcoexist, BTC_MEDIA_DISCONNECT);

	halbtc8822b2ant_post_state_to_bt(
		btcoexist, BT_8822B_2ANT_SCOREBOARD_ACTIVE, false);
	halbtc8822b2ant_post_state_to_bt(btcoexist,
					 BT_8822B_2ANT_SCOREBOARD_ONOFF, false);
}
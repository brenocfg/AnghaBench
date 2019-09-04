#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ arp_cnt; } ;
struct TYPE_3__ {int wifi_is_high_pri_task; int freeze_coexrun_by_btinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 scalar_t__ BTC_ASSOCIATE_5G_FINISH ; 
 scalar_t__ BTC_ASSOCIATE_5G_START ; 
 scalar_t__ BTC_ASSOCIATE_START ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  BT_8822B_1ANT_SCOREBOARD_SCAN ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_not_connected (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_not_connected_asso_auth (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8822b1ant_connect_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_connected = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ********** (connect notify) **********\n");

	halbtc8822b1ant_post_state_to_bt(btcoexist,
					 BT_8822B_1ANT_SCOREBOARD_SCAN, true);

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	if ((type == BTC_ASSOCIATE_5G_START) ||
	    (type == BTC_ASSOCIATE_5G_FINISH)) {
		if (type == BTC_ASSOCIATE_5G_START) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** (5G associate start notify) **********\n");

			halbtc8822b1ant_action_wifi_under5g(btcoexist);

		} else if (type == BTC_ASSOCIATE_5G_FINISH) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** (5G associate finish notify) **********\n");
		}

		return;
	}

	if (type == BTC_ASSOCIATE_START) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], 2G CONNECT START notify\n");

		coex_sta->wifi_is_high_pri_task = true;

		halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     FORCE_EXEC,
					     BT_8822B_1ANT_PHASE_2G_RUNTIME);

		coex_dm->arp_cnt = 0;

		halbtc8822b1ant_action_wifi_not_connected_asso_auth(btcoexist);

		coex_sta->freeze_coexrun_by_btinfo = true;

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], 2G CONNECT Finish notify\n");
		coex_sta->wifi_is_high_pri_task = false;
		coex_sta->freeze_coexrun_by_btinfo = false;

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
				   &wifi_connected);

		if (!wifi_connected) /* non-connected scan */
			halbtc8822b1ant_action_wifi_not_connected(btcoexist);
		else
			halbtc8822b1ant_action_wifi_connected(btcoexist);
	}
}
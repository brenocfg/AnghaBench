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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {int high_priority_tx; int high_priority_rx; int low_priority_tx; int low_priority_rx; int bt_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_SET_ACT_LEAVE_LPS ; 
 int /*<<< orphan*/  BTC_SET_ACT_NORMAL_LPS ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_DISABLE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8723b1ant_action_wifi_only (struct btc_coexist*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_monitor_bt_enable_disable(struct btc_coexist
						      *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u32 bt_disable_cnt;
	bool bt_active = true, bt_disabled = false;

	if (coex_sta->high_priority_tx == 0 &&
	    coex_sta->high_priority_rx == 0 && coex_sta->low_priority_tx == 0 &&
	    coex_sta->low_priority_rx == 0)
		bt_active = false;
	if (coex_sta->high_priority_tx == 0xffff &&
	    coex_sta->high_priority_rx == 0xffff &&
	    coex_sta->low_priority_tx == 0xffff &&
	    coex_sta->low_priority_rx == 0xffff)
		bt_active = false;
	if (bt_active) {
		bt_disable_cnt = 0;
		bt_disabled = false;
	} else {
		bt_disable_cnt++;
		if (bt_disable_cnt >= 2)
			bt_disabled = true;
	}
	if (coex_sta->bt_disabled != bt_disabled) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is from %s to %s!!\n",
			 (coex_sta->bt_disabled ? "disabled" : "enabled"),
			 (bt_disabled ? "disabled" : "enabled"));

		coex_sta->bt_disabled = bt_disabled;
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_DISABLE,
				   &bt_disabled);
		if (bt_disabled) {
			halbtc8723b1ant_action_wifi_only(btcoexist);
			btcoexist->btc_set(btcoexist, BTC_SET_ACT_LEAVE_LPS,
					   NULL);
			btcoexist->btc_set(btcoexist, BTC_SET_ACT_NORMAL_LPS,
					   NULL);
		}
	}
}
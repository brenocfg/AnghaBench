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
struct btc_coexist {scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int under_lps; scalar_t__ force_lps_ctrl; } ;

/* Variables and functions */
 scalar_t__ BTC_LPS_DISABLE ; 
 scalar_t__ BTC_LPS_ENABLE ; 
 int /*<<< orphan*/  BT_8822B_1ANT_SCOREBOARD_ACTIVE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_query_bt_info (struct btc_coexist*) ; 

void ex_btc8822b1ant_lps_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static bool pre_force_lps_on;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;

	if (type == BTC_LPS_ENABLE) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], LPS ENABLE notify\n");
		coex_sta->under_lps = true;

		if (coex_sta->force_lps_ctrl) { /* LPS No-32K */
			/* Write WL "Active" in Score-board for PS-TDMA */
			pre_force_lps_on = true;
			halbtc8822b1ant_post_state_to_bt(
				btcoexist, BT_8822B_1ANT_SCOREBOARD_ACTIVE,
				true);
		} else {
			/* LPS-32K, need check if this h2c 0x71 can work??
			 * (2015/08/28)
			 */
			/* Write WL "Non-Active" in Score-board for Native-PS */
			pre_force_lps_on = false;
			halbtc8822b1ant_post_state_to_bt(
				btcoexist, BT_8822B_1ANT_SCOREBOARD_ACTIVE,
				false);
		}
	} else if (type == BTC_LPS_DISABLE) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], LPS DISABLE notify\n");
		coex_sta->under_lps = false;

		/* Write WL "Active" in Score-board for LPS off */
		halbtc8822b1ant_post_state_to_bt(
			btcoexist, BT_8822B_1ANT_SCOREBOARD_ACTIVE, true);

		if ((!pre_force_lps_on) && (!coex_sta->force_lps_ctrl))
			halbtc8822b1ant_query_bt_info(btcoexist);
	}
}
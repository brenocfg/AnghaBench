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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {int bt_disabled; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_DISABLE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_low_penalty_ra (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_read_score_board (struct btc_coexist*,int*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
halbtc8822b2ant_monitor_bt_enable_disable(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u32 bt_disable_cnt;
	bool bt_active = true, bt_disabled = false, wifi_under_5g = false;
	u16 u16tmp;

	/* This function check if bt is disabled */

	/* Read BT on/off status from scoreboard[1],
	 * enable this only if BT patch support this feature
	 */
	halbtc8822b2ant_read_score_board(btcoexist, &u16tmp);

	bt_active = u16tmp & BIT(1);

	if (bt_active) {
		bt_disable_cnt = 0;
		bt_disabled = false;
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_DISABLE,
				   &bt_disabled);
	} else {
		bt_disable_cnt++;
		if (bt_disable_cnt >= 10) {
			bt_disabled = true;
			bt_disable_cnt = 10;
		}

		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_DISABLE,
				   &bt_disabled);
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if ((wifi_under_5g) || (bt_disabled))
		halbtc8822b2ant_low_penalty_ra(btcoexist, NORMAL_EXEC, false);
	else
		halbtc8822b2ant_low_penalty_ra(btcoexist, NORMAL_EXEC, true);

	if (coex_sta->bt_disabled != bt_disabled) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is from %s to %s!!\n",
			 (coex_sta->bt_disabled ? "disabled" : "enabled"),
			 (bt_disabled ? "disabled" : "enabled"));
		coex_sta->bt_disabled = bt_disabled;
	}
}
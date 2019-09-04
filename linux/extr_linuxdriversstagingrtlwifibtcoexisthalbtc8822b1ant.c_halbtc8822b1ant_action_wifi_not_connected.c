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
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void
halbtc8822b1ant_action_wifi_not_connected(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool rf4ce_enabled = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ********** (wifi not connect) **********\n");

	/* tdma and coex table */
	if (rf4ce_enabled) {
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x45e, 0x8, 0x1);

		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 50);

		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
		return;
	}
	halbtc8822b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);

	halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_1ANT_PHASE_2G_RUNTIME);

	halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
}
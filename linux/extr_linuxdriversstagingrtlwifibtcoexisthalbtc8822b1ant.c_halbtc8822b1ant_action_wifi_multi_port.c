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
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
halbtc8822b1ant_action_wifi_multi_port(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex],action_wifi_multi_port\n");

	halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);

	halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, NORMAL_EXEC,
				     BT_8822B_1ANT_PHASE_2G_RUNTIME);

	halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
}
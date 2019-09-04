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
struct btc_coexist {int stop_coex_dm; int auto_report_1ant; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_init_hw_config (struct btc_coexist*,int,int) ; 

void ex_btc8822b1ant_init_hw_config(struct btc_coexist *btcoexist,
				    bool wifi_only)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ********** (ini hw config) **********\n");

	halbtc8822b1ant_init_hw_config(btcoexist, true, wifi_only);
	btcoexist->stop_coex_dm = false;
	btcoexist->auto_report_1ant = true;
}
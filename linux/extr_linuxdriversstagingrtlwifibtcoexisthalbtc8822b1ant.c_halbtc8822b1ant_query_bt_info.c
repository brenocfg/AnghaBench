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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ bt_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void halbtc8822b1ant_query_bt_info(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = {0};

	if (coex_sta->bt_disabled) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], No query BT info because BT is disabled!\n");
		return;
	}

	h2c_parameter[0] |= BIT(0); /* trigger */

	btcoexist->btc_fill_h2c(btcoexist, 0x61, 1, h2c_parameter);

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], WL query BT info!!\n");
}
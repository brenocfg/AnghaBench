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
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {int under_ips; } ;

/* Variables and functions */
 scalar_t__ BTC_IPS_ENTER ; 
 scalar_t__ BTC_IPS_LEAVE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8192e2ant_coex_all_off (struct btc_coexist*) ; 
 TYPE_1__* coex_sta ; 

void ex_btc8192e2ant_ips_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (BTC_IPS_ENTER == type) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;
		btc8192e2ant_coex_all_off(btcoexist);
	} else if (BTC_IPS_LEAVE == type) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;
	}
}
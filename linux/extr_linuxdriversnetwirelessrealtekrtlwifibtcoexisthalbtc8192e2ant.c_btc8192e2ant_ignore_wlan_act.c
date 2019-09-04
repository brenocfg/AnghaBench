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
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {int cur_ignore_wlan_act; int pre_ignore_wlan_act; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8192e2ant_set_fw_ignore_wlan_act (struct btc_coexist*,int) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static void btc8192e2ant_ignore_wlan_act(struct btc_coexist *btcoexist,
					 bool force_exec, bool enable)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], %s turn Ignore WlanAct %s\n",
		 (force_exec ? "force to" : ""), (enable ? "ON" : "OFF"));
	coex_dm->cur_ignore_wlan_act = enable;

	if (!force_exec) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], bPreIgnoreWlanAct = %d ",
			 coex_dm->pre_ignore_wlan_act);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "bCurIgnoreWlanAct = %d!!\n",
			 coex_dm->cur_ignore_wlan_act);

		if (coex_dm->pre_ignore_wlan_act ==
		    coex_dm->cur_ignore_wlan_act)
			return;
	}
	btc8192e2ant_set_fw_ignore_wlan_act(btcoexist, enable);

	coex_dm->pre_ignore_wlan_act = coex_dm->cur_ignore_wlan_act;
}
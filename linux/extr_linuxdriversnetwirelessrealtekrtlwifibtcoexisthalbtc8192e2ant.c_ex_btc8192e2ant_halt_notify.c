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
 int /*<<< orphan*/  BTC_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8192e2ant_ignore_wlan_act (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ex_btc8192e2ant_media_status_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 

void ex_btc8192e2ant_halt_notify(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Halt notify\n");

	btc8192e2ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);
	ex_btc8192e2ant_media_status_notify(btcoexist, BTC_MEDIA_DISCONNECT);
}
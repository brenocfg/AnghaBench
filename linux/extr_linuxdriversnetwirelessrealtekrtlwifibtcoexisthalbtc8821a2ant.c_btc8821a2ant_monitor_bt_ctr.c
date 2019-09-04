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
struct btc_bt_link_info {int slave_role; } ;
struct btc_coexist {int (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int high_priority_tx; int high_priority_rx; int low_priority_tx; int low_priority_rx; int /*<<< orphan*/  under_ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int MASKHWORD ; 
 int MASKLWORD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 TYPE_1__* coex_sta ; 
 int stub1 (struct btc_coexist*,int) ; 
 int stub2 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void btc8821a2ant_monitor_bt_ctr(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u32 reg_hp_txrx, reg_lp_txrx, u4tmp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;

	reg_hp_txrx = 0x770;
	reg_lp_txrx = 0x774;

	u4tmp = btcoexist->btc_read_4byte(btcoexist, reg_hp_txrx);
	reg_hp_tx = u4tmp & MASKLWORD;
	reg_hp_rx = (u4tmp & MASKHWORD) >> 16;

	u4tmp = btcoexist->btc_read_4byte(btcoexist, reg_lp_txrx);
	reg_lp_tx = u4tmp & MASKLWORD;
	reg_lp_rx = (u4tmp & MASKHWORD) >> 16;

	coex_sta->high_priority_tx = reg_hp_tx;
	coex_sta->high_priority_rx = reg_hp_rx;
	coex_sta->low_priority_tx = reg_lp_tx;
	coex_sta->low_priority_rx = reg_lp_rx;

	if ((coex_sta->low_priority_rx >= 950) &&
	    (coex_sta->low_priority_rx >= coex_sta->low_priority_tx) &&
	    (!coex_sta->under_ips))
		bt_link_info->slave_role = true;
	else
		bt_link_info->slave_role = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], High Priority Tx/Rx (reg 0x%x) = 0x%x(%d)/0x%x(%d)\n",
		    reg_hp_txrx, reg_hp_tx, reg_hp_tx, reg_hp_rx, reg_hp_rx);
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Low Priority Tx/Rx (reg 0x%x) = 0x%x(%d)/0x%x(%d)\n",
		 reg_lp_txrx, reg_lp_tx, reg_lp_tx, reg_lp_rx, reg_lp_rx);

	/* reset counter */
	btcoexist->btc_write_1byte(btcoexist, 0x76e, 0xc);
}
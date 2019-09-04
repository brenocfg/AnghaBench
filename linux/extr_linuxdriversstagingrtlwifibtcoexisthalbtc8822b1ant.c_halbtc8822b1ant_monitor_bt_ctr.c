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
typedef  int u8 ;
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {int slave_role; scalar_t__ hid_only; } ;
struct btc_coexist {int (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int high_priority_tx; int high_priority_rx; int low_priority_tx; int low_priority_rx; int is_tdma_btautoslot_hang; int is_hid_low_pri_tx_overhead; scalar_t__ is_tdma_btautoslot; scalar_t__ bt_link_exist; int /*<<< orphan*/  c2h_bt_inquiry_page; int /*<<< orphan*/  under_ips; int /*<<< orphan*/  pop_event_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int MASKHWORD ; 
 int MASKLWORD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_query_bt_info (struct btc_coexist*) ; 
 int stub1 (struct btc_coexist*,int) ; 
 int stub2 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void halbtc8822b1ant_monitor_bt_ctr(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u32 reg_hp_txrx, reg_lp_txrx, u32tmp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;
	static u8 num_of_bt_counter_chk, cnt_slave, cnt_autoslot_hang;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	reg_hp_txrx = 0x770;
	reg_lp_txrx = 0x774;

	u32tmp = btcoexist->btc_read_4byte(btcoexist, reg_hp_txrx);
	reg_hp_tx = u32tmp & MASKLWORD;
	reg_hp_rx = (u32tmp & MASKHWORD) >> 16;

	u32tmp = btcoexist->btc_read_4byte(btcoexist, reg_lp_txrx);
	reg_lp_tx = u32tmp & MASKLWORD;
	reg_lp_rx = (u32tmp & MASKHWORD) >> 16;

	coex_sta->high_priority_tx = reg_hp_tx;
	coex_sta->high_priority_rx = reg_hp_rx;
	coex_sta->low_priority_tx = reg_lp_tx;
	coex_sta->low_priority_rx = reg_lp_rx;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Hi-Pri Rx/Tx: %d/%d, Lo-Pri Rx/Tx: %d/%d\n",
		 reg_hp_rx, reg_hp_tx, reg_lp_rx, reg_lp_tx);

	/* reset counter */
	btcoexist->btc_write_1byte(btcoexist, 0x76e, 0xc);

	if ((coex_sta->low_priority_tx > 1150) &&
	    (!coex_sta->c2h_bt_inquiry_page))
		coex_sta->pop_event_cnt++;

	if ((coex_sta->low_priority_rx >= 1150) &&
	    (coex_sta->low_priority_rx >= coex_sta->low_priority_tx) &&
	    (!coex_sta->under_ips) && (!coex_sta->c2h_bt_inquiry_page) &&
	    (coex_sta->bt_link_exist)) {
		if (cnt_slave >= 3) {
			bt_link_info->slave_role = true;
			cnt_slave = 3;
		} else {
			cnt_slave++;
		}
	} else {
		if (cnt_slave == 0) {
			bt_link_info->slave_role = false;
			cnt_slave = 0;
		} else {
			cnt_slave--;
		}
	}

	if (coex_sta->is_tdma_btautoslot) {
		if ((coex_sta->low_priority_tx >= 1300) &&
		    (coex_sta->low_priority_rx <= 150)) {
			if (cnt_autoslot_hang >= 2) {
				coex_sta->is_tdma_btautoslot_hang = true;
				cnt_autoslot_hang = 2;
			} else {
				cnt_autoslot_hang++;
			}
		} else {
			if (cnt_autoslot_hang == 0) {
				coex_sta->is_tdma_btautoslot_hang = false;
				cnt_autoslot_hang = 0;
			} else {
				cnt_autoslot_hang--;
			}
		}
	}

	if (bt_link_info->hid_only) {
		if (coex_sta->low_priority_rx > 50)
			coex_sta->is_hid_low_pri_tx_overhead = true;
		else
			coex_sta->is_hid_low_pri_tx_overhead = false;
	}

	if ((coex_sta->high_priority_tx == 0) &&
	    (coex_sta->high_priority_rx == 0) &&
	    (coex_sta->low_priority_tx == 0) &&
	    (coex_sta->low_priority_rx == 0)) {
		num_of_bt_counter_chk++;

		if (num_of_bt_counter_chk >= 3) {
			halbtc8822b1ant_query_bt_info(btcoexist);
			num_of_bt_counter_chk = 0;
		}
	}
}
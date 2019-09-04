#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {scalar_t__ slave_role; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_4__ {int cur_ps_tdma_on; int pre_ps_tdma_on; int /*<<< orphan*/  cur_ps_tdma; int /*<<< orphan*/  pre_ps_tdma; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_set_ps_state_fail; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_fw_pstdma (struct btc_coexist*,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b1ant_ps_tdma(struct btc_coexist *btcoexist,
				    bool force_exec, bool turn_on, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_busy = false;
	static u8 ps_tdma_byte4_modify, pre_ps_tdma_byte4_modify;
	static bool pre_wifi_busy;

	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	if (wifi_busy != pre_wifi_busy) {
		force_exec = true;
		pre_wifi_busy = wifi_busy;
	}

	/* 0x778 = 0x1 at wifi slot (no blocking BT Low-Pri pkts) */
	if (bt_link_info->slave_role)
		ps_tdma_byte4_modify = 0x1;
	else
		ps_tdma_byte4_modify = 0x0;

	if (pre_ps_tdma_byte4_modify != ps_tdma_byte4_modify) {
		force_exec = true;
		pre_ps_tdma_byte4_modify = ps_tdma_byte4_modify;
	}

	if (!force_exec) {
		if ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma)) {
			RT_TRACE(
				rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Skip TDMA because no change TDMA(%s, %d)\n",
				(coex_dm->cur_ps_tdma_on ? "on" : "off"),
				coex_dm->cur_ps_tdma);
			return;
		}
	}

	if (coex_dm->cur_ps_tdma_on) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ********** TDMA(on, %d) **********\n",
			 coex_dm->cur_ps_tdma);

		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x550, 0x8, 0x1); /* enable TBTT nterrupt */
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ********** TDMA(off, %d) **********\n",
			 coex_dm->cur_ps_tdma);
	}

	if (turn_on) {
		/* enable TBTT nterrupt */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x550, 0x8, 0x1);

		switch (type) {
		default:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x35,
						      0x03, 0x11, 0x11);
			break;
		case 1:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x3a,
						      0x03, 0x11, 0x10);
			break;
		case 3:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x30,
						      0x03, 0x10, 0x50);
			break;
		case 4:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x21,
						      0x03, 0x10, 0x50);
			break;
		case 5:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x15,
						      0x3, 0x11, 0x11);
			break;
		case 6:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x20,
						      0x3, 0x11, 0x10);
			break;
		case 7:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x51, 0x10, 0x03, 0x10,
				0x54 | ps_tdma_byte4_modify);
			break;
		case 8:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x51, 0x10, 0x03, 0x10,
				0x14 | ps_tdma_byte4_modify);
			break;
		case 11:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x61, 0x25, 0x03, 0x11,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 12:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x51, 0x30, 0x03, 0x10,
				0x50 | ps_tdma_byte4_modify);
			break;
		case 13:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x51, 0x10, 0x07, 0x10,
				0x54 | ps_tdma_byte4_modify);
			break;
		case 14:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x51, 0x15, 0x03, 0x10,
				0x50 | ps_tdma_byte4_modify);
			break;
		case 15:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x51, 0x20, 0x03, 0x10,
				0x10 | ps_tdma_byte4_modify);
			break;
		case 17:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x61, 0x10, 0x03, 0x11,
				0x14 | ps_tdma_byte4_modify);
			break;
		case 18:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x51, 0x10, 0x03, 0x10,
				0x50 | ps_tdma_byte4_modify);
			break;

		case 20:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x30,
						      0x03, 0x11, 0x10);
			break;
		case 22:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x25,
						      0x03, 0x11, 0x10);
			break;
		case 27:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x10,
						      0x03, 0x11, 0x15);
			break;
		case 32:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x35,
						      0x3, 0x11, 0x11);
			break;
		case 33:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x35,
						      0x03, 0x11, 0x10);
			break;
		case 41:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x45,
						      0x3, 0x11, 0x11);
			break;
		case 42:
			halbtc8822b1ant_set_fw_pstdma(
				btcoexist, 0x51, 0x1e, 0x3, 0x10,
				0x14 | ps_tdma_byte4_modify);
			break;
		case 43:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x45,
						      0x3, 0x10, 0x14);
			break;
		case 44:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x25,
						      0x3, 0x10, 0x10);
			break;
		case 45:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x29,
						      0x3, 0x10, 0x10);
			break;
		case 46:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x1a,
						      0x3, 0x10, 0x10);
			break;
		case 47:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x32,
						      0x3, 0x10, 0x10);
			break;
		case 48:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x29,
						      0x3, 0x10, 0x10);
			break;
		case 49:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x55, 0x10,
						      0x3, 0x10, 0x54);
			break;
		case 50:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x51, 0x4a,
						      0x3, 0x10, 0x10);
			break;
		case 51:
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x61, 0x35,
						      0x3, 0x10, 0x11);
			break;
		}
	} else {
		switch (type) {
		case 0:
		default: /* Software control, Antenna at BT side */
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x0, 0x0, 0x0,
						      0x0, 0x0);
			break;
		case 8: /* PTA Control */
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x8, 0x0, 0x0,
						      0x0, 0x0);
			break;
		case 9: /* Software control, Antenna at WiFi side */
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x0, 0x0, 0x0,
						      0x0, 0x0);
			break;
		case 10: /* under 5G , 0x778=1*/
			halbtc8822b1ant_set_fw_pstdma(btcoexist, 0x0, 0x0, 0x0,
						      0x0, 0x0);

			break;
		}
	}

	if (!coex_sta->is_set_ps_state_fail) {
		/* update pre state */
		coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
		coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
	}
}
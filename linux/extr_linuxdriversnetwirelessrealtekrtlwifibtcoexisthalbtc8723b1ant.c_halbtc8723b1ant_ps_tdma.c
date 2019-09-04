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
struct btc_bt_link_info {scalar_t__ a2dp_exist; scalar_t__ slave_role; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; } ;
typedef  int s8 ;
struct TYPE_4__ {int cur_ps_tdma_on; int cur_ps_tdma; int pre_ps_tdma_on; scalar_t__ pre_ps_tdma; } ;
struct TYPE_3__ {int scan_ap_num; int a2dp_bit_pool; int /*<<< orphan*/  force_lps_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_PTA ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_fw_ps_tdma (struct btc_coexist*,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_ps_tdma(struct btc_coexist *btcoexist,
				    bool force_exec, bool turn_on, u8 type)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_busy = false;
	u8 rssi_adjust_val = 0;
	u8 ps_tdma_byte0_val = 0x51;
	u8 ps_tdma_byte3_val = 0x10;
	u8 ps_tdma_byte4_val = 0x50;
	s8 wifi_duration_adjust = 0x0;
	static bool pre_wifi_busy;

	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	if (wifi_busy != pre_wifi_busy) {
		force_exec = true;
		pre_wifi_busy = wifi_busy;
	}

	if (!force_exec) {
		if ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			return;
	}

	if (coex_sta->scan_ap_num <= 5) {
		wifi_duration_adjust = 5;

		if (coex_sta->a2dp_bit_pool >= 35)
			wifi_duration_adjust = -10;
		else if (coex_sta->a2dp_bit_pool >= 45)
			wifi_duration_adjust = -15;
	} else if (coex_sta->scan_ap_num >= 40) {
		wifi_duration_adjust = -15;

		if (coex_sta->a2dp_bit_pool < 35)
			wifi_duration_adjust = -5;
		else if (coex_sta->a2dp_bit_pool < 45)
			wifi_duration_adjust = -10;
	} else if (coex_sta->scan_ap_num >= 20) {
		wifi_duration_adjust = -10;

		if (coex_sta->a2dp_bit_pool >= 45)
			wifi_duration_adjust = -15;
	} else {
		wifi_duration_adjust = 0;

		if (coex_sta->a2dp_bit_pool >= 35)
			wifi_duration_adjust = -10;
		else if (coex_sta->a2dp_bit_pool >= 45)
			wifi_duration_adjust = -15;
	}

	if ((type == 1) || (type == 2) || (type == 9) || (type == 11) ||
	    (type == 101) || (type == 102) || (type == 109) || (type == 111)) {
		if (!coex_sta->force_lps_on) {
			/* Native power save TDMA, only for A2DP-only case
			 * 1/2/9/11 while wifi noisy threshold > 30
			 */

			/* no null-pkt */
			ps_tdma_byte0_val = 0x61;
			/* no tx-pause at BT-slot */
			ps_tdma_byte3_val = 0x11;
			/* 0x778 = d/1 toggle, no dynamic slot */
			ps_tdma_byte4_val = 0x10;
		} else {
			/* null-pkt */
			ps_tdma_byte0_val = 0x51;
			/* tx-pause at BT-slot */
			ps_tdma_byte3_val = 0x10;
			/* 0x778 = d/1 toggle, dynamic slot */
			ps_tdma_byte4_val = 0x50;
		}
	} else if ((type == 3) || (type == 13) || (type == 14) ||
		   (type == 103) || (type == 113) || (type == 114)) {
		/* null-pkt */
		ps_tdma_byte0_val = 0x51;
		/* tx-pause at BT-slot */
		ps_tdma_byte3_val = 0x10;
		/* 0x778 = d/1 toggle, no dynamic slot */
		ps_tdma_byte4_val = 0x10;
	} else { /* native power save case */
		/* no null-pkt */
		ps_tdma_byte0_val = 0x61;
		/* no tx-pause at BT-slot */
		ps_tdma_byte3_val = 0x11;
		/* 0x778 = d/1 toggle, no dynamic slot */
		ps_tdma_byte4_val = 0x11;
		/* psTdmaByte4Va is not define for 0x778 = d/1, 1/1 case */
	}

	/* if (bt_link_info->slave_role) */
	if ((bt_link_info->slave_role) && (bt_link_info->a2dp_exist))
		/* 0x778 = 0x1 at wifi slot (no blocking BT Low-Pri pkts) */
		ps_tdma_byte4_val = ps_tdma_byte4_val | 0x1;

	if (type > 100) {
		/* set antenna control by SW	 */
		ps_tdma_byte0_val = ps_tdma_byte0_val | 0x82;
		/* set antenna no toggle, control by antenna diversity */
		ps_tdma_byte3_val = ps_tdma_byte3_val | 0x60;
	}

	if (turn_on) {
		switch (type) {
		default:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x1a,
						      0x1a, 0x0,
						      ps_tdma_byte4_val);
			break;
		case 1:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val,
				0x3a + wifi_duration_adjust, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);

			rssi_adjust_val = 11;
			break;
		case 2:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val,
				0x2d + wifi_duration_adjust, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 3:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x30, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 4:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x15,
						      0x3, 0x14, 0x0);
			break;
		case 5:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x1f, 0x3,
				ps_tdma_byte3_val, 0x11);
			break;
		case 6:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x20, 0x3,
				ps_tdma_byte3_val, 0x11);
			break;
		case 7:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xc,
						       0x5, 0x0, 0x0);
			break;
		case 8:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x25,
						      0x3, 0x10, 0x0);
			break;
		case 9:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 10:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xa,
						       0xa, 0x0, 0x40);
			break;
		case 11:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 12:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x0a,
						      0x0a, 0x0, 0x50);
			break;
		case 13:
			if (coex_sta->scan_ap_num <= 3)
				halbtc8723b1ant_set_fw_ps_tdma(
					btcoexist, ps_tdma_byte0_val, 0x40, 0x3,
					ps_tdma_byte3_val, ps_tdma_byte4_val);
			else
				halbtc8723b1ant_set_fw_ps_tdma(
					btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
					ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 14:
			if (coex_sta->scan_ap_num <= 3)
				halbtc8723b1ant_set_fw_ps_tdma(
					btcoexist, 0x51, 0x30, 0x3, 0x10, 0x50);
			else
				halbtc8723b1ant_set_fw_ps_tdma(
					btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
					ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 15:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xa,
						       0x3, 0x8, 0x0);
			break;
		case 16:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x15,
						      0x3, 0x10, 0x0);
			break;
		case 18:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x25,
						      0x3, 0x10, 0x0);
			break;
		case 20:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x3f, 0x03,
				ps_tdma_byte3_val, 0x10);
			break;
		case 21:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x61, 0x25,
						      0x03, 0x11, 0x11);
			break;
		case 22:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x25, 0x03,
				ps_tdma_byte3_val, 0x10);
			break;
		case 23:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						      0x3, 0x31, 0x18);
			break;
		case 24:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						      0x3, 0x31, 0x18);
			break;
		case 25:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0xa,
						       0x3, 0x31, 0x18);
			break;
		case 26:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0xa,
						       0x3, 0x31, 0x18);
			break;
		case 27:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						      0x3, 0x31, 0x98);
			break;
		case 28:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x69, 0x25,
						      0x3, 0x31, 0x0);
			break;
		case 29:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xab, 0x1a,
						      0x1a, 0x1, 0x10);
			break;
		case 30:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x30,
						       0x3, 0x10, 0x10);
			break;
		case 31:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1a,
						      0x1a, 0, 0x58);
			break;
		case 32:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x35, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 33:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x35, 0x3,
				ps_tdma_byte3_val, 0x10);
			break;
		case 34:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x53, 0x1a,
						      0x1a, 0x0, 0x10);
			break;
		case 35:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x63, 0x1a,
						      0x1a, 0x0, 0x10);
			break;
		case 36:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x12,
						      0x3, 0x14, 0x50);
			break;
		case 40:
			/* SoftAP only with no sta associated,BT disable ,TDMA
			 * mode for power saving
			 *
			 * here softap mode screen off will cost 70-80mA for
			 * phone
			 */
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x23, 0x18,
						      0x00, 0x10, 0x24);
			break;

		case 101:
			/* for 1-Ant translate to 2-Ant	 */
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val,
				0x3a + wifi_duration_adjust, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 102:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val,
				0x2d + wifi_duration_adjust, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 103:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x3a, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 105:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x15, 0x3,
				ps_tdma_byte3_val, 0x11);
			break;
		case 106:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x20, 0x3,
				ps_tdma_byte3_val, 0x11);
			break;
		case 109:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 111:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 113:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 114:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 120:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x3f, 0x03,
				ps_tdma_byte3_val, 0x10);
			break;
		case 122:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x25, 0x03,
				ps_tdma_byte3_val, 0x10);
			break;
		case 132:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x25, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			break;
		case 133:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x25, 0x03,
				ps_tdma_byte3_val, 0x11);
			break;
		}
	} else {
		/* disable PS tdma */
		switch (type) {
		case 8: /* PTA Control */
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x8, 0x0,
						       0x0, 0x0, 0x0);
			halbtc8723b1ant_set_ant_path(btcoexist,
						     BTC_ANT_PATH_PTA,
						     FORCE_EXEC,
						     false, false);
			break;
		case 0:
		default:
			/* Software control, Antenna at BT side */
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0,
						       0x0, 0x0, 0x0);
			break;
		case 1: /* 2-Ant, 0x778=3, antenna control by ant diversity */
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						       0x48, 0x0);
			break;
		}
	}
	rssi_adjust_val = 0;
	btcoexist->btc_set(btcoexist,
			   BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE,
			   &rssi_adjust_val);

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
}
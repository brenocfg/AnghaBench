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
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {int cur_ps_tdma_on; int cur_ps_tdma; int pre_ps_tdma_on; int pre_ps_tdma; } ;

/* Variables and functions */
 scalar_t__ BTC_RSSI_HIGH (int) ; 
 int /*<<< orphan*/  BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES ; 
 int /*<<< orphan*/  BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int btc8821a2ant_bt_rssi_state (struct btc_coexist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a2ant_set_fw_ps_tdma (struct btc_coexist*,int,int,int,int,int) ; 
 int btc8821a2ant_wifi_rssi_state (struct btc_coexist*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static void btc8821a2ant_ps_tdma(struct btc_coexist *btcoexist,
				 bool force_exec, bool turn_on, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	u8 wifi_rssi_state, bt_rssi_state;

	wifi_rssi_state = btc8821a2ant_wifi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist, 2,
				BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	if (!(BTC_RSSI_HIGH(wifi_rssi_state) &&
	      BTC_RSSI_HIGH(bt_rssi_state)) &&
	    turn_on) {
		/* for WiFi RSSI low or BT RSSI low */
		type = type + 100;
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], %s turn %s PS TDMA, type = %d\n",
		 (force_exec ? "force to" : ""), (turn_on ? "ON" : "OFF"),
		 type);
	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	if (!force_exec) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], pre_ps_tdma_on = %d, cur_ps_tdma_on = %d!!\n",
			 coex_dm->pre_ps_tdma_on, coex_dm->cur_ps_tdma_on);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], pre_ps_tdma = %d, cur_ps_tdma = %d!!\n",
			 coex_dm->pre_ps_tdma, coex_dm->cur_ps_tdma);

		if ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			return;
	}
	if (turn_on) {
		switch (type) {
		case 1:
		default:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1, 0x90);
			break;
		case 2:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x2d,
						    0x03, 0xf1, 0x90);
			break;
		case 3:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1, 0x90);
			break;
		case 4:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x03, 0xf1, 0x90);
			break;
		case 5:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x3, 0x70, 0x90);
			break;
		case 6:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x2d,
						    0x3, 0x70, 0x90);
			break;
		case 7:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70, 0x90);
			break;
		case 8:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x10,
						    0x3, 0x70, 0x90);
			break;
		case 9:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1, 0x90);
			break;
		case 10:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x2d,
						    0x03, 0xf1, 0x90);
			break;
		case 11:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1, 0x90);
			break;
		case 12:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0xf1, 0x90);
			break;
		case 13:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x3, 0x70, 0x90);
			break;
		case 14:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x2d,
						    0x3, 0x70, 0x90);
			break;
		case 15:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70, 0x90);
			break;
		case 16:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0x70, 0x90);
			break;
		case 17:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x2f,
						    0x2f, 0x60, 0x90);
			break;
		case 18:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x5, 0x5,
						    0xe1, 0x90);
			break;
		case 19:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0xe1, 0x90);
			break;
		case 20:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0x60, 0x90);
			break;
		case 21:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70, 0x90);
			break;
		case 23:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1e,
						    0x03, 0xf0, 0x14);
			break;
		case 24:
		case 124:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x3c,
						    0x03, 0x70, 0x50);
			break;
		case 25:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x14,
						    0x03, 0xf1, 0x90);
			break;
		case 26:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x30,
						    0x03, 0xf1, 0x90);
			break;
		case 71:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1, 0x90);
			break;
		case 101:
		case 105:
		case 171:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x3a,
						    0x03, 0x70, 0x50);
			break;
		case 102:
		case 106:
		case 110:
		case 114:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x2d,
						    0x03, 0x70, 0x50);
			break;
		case 103:
		case 107:
		case 111:
		case 115:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1c,
						    0x03, 0x70, 0x50);
			break;
		case 104:
		case 108:
		case 112:
		case 116:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x10,
						    0x03, 0x70, 0x50);
			break;
		case 109:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1, 0x90);
			break;
		case 113:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0x70, 0x90);
			break;
		case 121:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70, 0x90);
			break;
		case 22:
		case 122:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x35,
						    0x03, 0x71, 0x11);
			break;
		case 123:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1c,
						    0x03, 0x70, 0x54);
			break;
		case 125:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x14,
						    0x03, 0x70, 0x50);
			break;
		case 126:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x30,
						    0x03, 0x70, 0x50);
			break;
		}
	} else {
		/* disable PS tdma */
		switch (type) {
		case 0:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x40, 0x0);
			break;
		case 1:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x48, 0x0);
			break;
		default:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x40, 0x0);
			break;
		}
	}

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
}
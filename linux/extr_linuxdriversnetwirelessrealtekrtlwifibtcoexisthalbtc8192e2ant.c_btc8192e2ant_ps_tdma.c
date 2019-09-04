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
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {int cur_ps_tdma_on; int cur_ps_tdma; int pre_ps_tdma_on; int pre_ps_tdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8192e2ant_set_fw_ps_tdma (struct btc_coexist*,int,int,int,int,int) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void btc8192e2ant_ps_tdma(struct btc_coexist *btcoexist,
				 bool force_exec, bool turn_on, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], %s turn %s PS TDMA, type=%d\n",
		 (force_exec ? "force to" : ""),
		 (turn_on ? "ON" : "OFF"), type);
	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	if (!force_exec) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], bPrePsTdmaOn = %d, bCurPsTdmaOn = %d!!\n",
			 coex_dm->pre_ps_tdma_on, coex_dm->cur_ps_tdma_on);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], prePsTdma = %d, curPsTdma = %d!!\n",
			 coex_dm->pre_ps_tdma, coex_dm->cur_ps_tdma);

		if ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			return;
	}
	if (turn_on) {
		switch (type) {
		case 1:
		default:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0xe1, 0x90);
			break;
		case 2:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x12, 0xe1, 0x90);
			break;
		case 3:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1, 0x90);
			break;
		case 4:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0xf1, 0x90);
			break;
		case 5:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0x60, 0x90);
			break;
		case 6:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x12, 0x60, 0x90);
			break;
		case 7:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70, 0x90);
			break;
		case 8:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x10,
						    0x3, 0x70, 0x90);
			break;
		case 9:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0xe1, 0x10);
			break;
		case 10:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x12, 0xe1, 0x10);
			break;
		case 11:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1, 0x10);
			break;
		case 12:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0xf1, 0x10);
			break;
		case 13:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0xe0, 0x10);
			break;
		case 14:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x12, 0xe0, 0x10);
			break;
		case 15:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf0, 0x10);
			break;
		case 16:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x3, 0xf0, 0x10);
			break;
		case 17:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0x61, 0x20,
						    0x03, 0x10, 0x10);
			break;
		case 18:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x5,
						    0x5, 0xe1, 0x90);
			break;
		case 19:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0xe1, 0x90);
			break;
		case 20:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0x60, 0x90);
			break;
		case 21:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70, 0x90);
			break;
		case 71:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0xe1, 0x90);
			break;
		}
	} else {
		/* disable PS tdma */
		switch (type) {
		default:
		case 0:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0x8, 0x0, 0x0,
						    0x0, 0x0);
			btcoexist->btc_write_1byte(btcoexist, 0x92c, 0x4);
			break;
		case 1:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x8, 0x0);
			mdelay(5);
			btcoexist->btc_write_1byte(btcoexist, 0x92c, 0x20);
			break;
		}
	}

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
}
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
typedef  int u8 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct btc_board_info {int /*<<< orphan*/  btdm_ant_pos; int /*<<< orphan*/  btdm_ant_num_by_ant_det; scalar_t__ btdm_ant_det_finish; } ;
struct btc_coexist {int dbg_mode_1ant; int stop_coex_dm; int (* btc_read_2byte ) (struct btc_coexist*,int) ;scalar_t__ chip_interface; int /*<<< orphan*/  (* btc_write_local_reg_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_2byte ) (struct btc_coexist*,int,int) ;struct btc_board_info board_info; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BTC_ANTENNA_AT_MAIN_PORT ; 
 scalar_t__ BTC_INTF_SDIO ; 
 scalar_t__ BTC_INTF_USB ; 
 int /*<<< orphan*/  BT_8822B_1ANT_GNT_BLOCK_RFC_BB ; 
 int /*<<< orphan*/  BT_8822B_1ANT_GNT_CTRL_BY_SW ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PCO_WLSIDE ; 
 int /*<<< orphan*/  BT_8822B_1ANT_SIG_STA_SET_TO_HIGH ; 
 int /*<<< orphan*/  BT_8822B_1ANT_SIG_STA_SET_TO_LOW ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  halbtc8822b1ant_enable_gnt_to_gpio (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ltecoex_pathcontrol_owner (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ltecoex_set_gnt_bt (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ltecoex_set_gnt_wl (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 

void ex_btc8822b1ant_power_on_setting(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_board_info *board_info = &btcoexist->board_info;
	u8 u8tmp = 0x0;
	u16 u16tmp = 0x0;

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"xxxxxxxxxxxxxxxx Execute 8822b 1-Ant PowerOn Setting!! xxxxxxxxxxxxxxxx\n");

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "Ant Det Finish = %s, Ant Det Number  = %d\n",
		 board_info->btdm_ant_det_finish ? "Yes" : "No",
		 board_info->btdm_ant_num_by_ant_det);

	btcoexist->dbg_mode_1ant = false;
	btcoexist->stop_coex_dm = true;

	/* enable BB, REG_SYS_FUNC_EN such that we can write 0x948 correctly. */
	u16tmp = btcoexist->btc_read_2byte(btcoexist, 0x2);
	btcoexist->btc_write_2byte(btcoexist, 0x2, u16tmp | BIT(0) | BIT(1));

	/* set Path control owner to WiFi */
	halbtc8822b1ant_ltecoex_pathcontrol_owner(btcoexist,
						  BT_8822B_1ANT_PCO_WLSIDE);

	/* set GNT_BT to high */
	halbtc8822b1ant_ltecoex_set_gnt_bt(btcoexist,
					   BT_8822B_1ANT_GNT_BLOCK_RFC_BB,
					   BT_8822B_1ANT_GNT_CTRL_BY_SW,
					   BT_8822B_1ANT_SIG_STA_SET_TO_HIGH);
	/* Set GNT_WL to low */
	halbtc8822b1ant_ltecoex_set_gnt_wl(
		btcoexist, BT_8822B_1ANT_GNT_BLOCK_RFC_BB,
		BT_8822B_1ANT_GNT_CTRL_BY_SW, BT_8822B_1ANT_SIG_STA_SET_TO_LOW);

	/* set WLAN_ACT = 0 */
	/* btcoexist->btc_write_1byte(btcoexist, 0x76e, 0x4); */

	/* SD1 Chunchu red x issue */
	btcoexist->btc_write_1byte(btcoexist, 0xff1a, 0x0);

	halbtc8822b1ant_enable_gnt_to_gpio(btcoexist, true);

	/* */
	/* S0 or S1 setting and Local register setting
	 * (By the setting fw can get ant number, S0/S1, ... info)
	 */
	/* Local setting bit define */
	/*	BIT0: "0" for no antenna inverse; "1" for antenna inverse  */
	/*	BIT1: "0" for internal switch; "1" for external switch */
	/*	BIT2: "0" for one antenna; "1" for two antenna */
	/* NOTE: here default all internal switch and 1-antenna ==>
	 *       BIT1=0 and BIT2=0
	 */

	u8tmp = 0;
	board_info->btdm_ant_pos = BTC_ANTENNA_AT_MAIN_PORT;

	if (btcoexist->chip_interface == BTC_INTF_USB)
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0xfe08, u8tmp);
	else if (btcoexist->chip_interface == BTC_INTF_SDIO)
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0x60, u8tmp);
}
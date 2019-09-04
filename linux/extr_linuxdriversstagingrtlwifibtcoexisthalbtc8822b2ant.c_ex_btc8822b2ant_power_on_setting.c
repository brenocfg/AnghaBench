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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct btc_board_info {char* btdm_ant_num_by_ant_det; scalar_t__ btdm_ant_det_finish; } ;
struct btc_coexist {int dbg_mode_2ant; int stop_coex_dm; int (* btc_read_2byte ) (struct btc_coexist*,int) ;scalar_t__ chip_interface; char* (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_local_reg_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_2byte ) (struct btc_coexist*,int,int) ;struct btc_board_info board_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int ant_det_is_ant_det_available; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 scalar_t__ BTC_INTF_PCI ; 
 scalar_t__ BTC_INTF_SDIO ; 
 scalar_t__ BTC_INTF_USB ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PHASE_COEX_POWERON ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  halbtc8822b2ant_enable_gnt_to_gpio (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ltecoex_indirect_read_reg (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_rfe_type (struct btc_coexist*) ; 
 TYPE_1__* psd_scan ; 
 int stub1 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 char* stub6 (struct btc_coexist*,int) ; 
 char* stub7 (struct btc_coexist*,int) ; 

void ex_btc8822b2ant_power_on_setting(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_board_info *board_info = &btcoexist->board_info;
	u8 u8tmp = 0x0;
	u16 u16tmp = 0x0;

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"xxxxxxxxxxxxxxxx Execute 8822b 2-Ant PowerOn Setting xxxxxxxxxxxxxxxx!!\n");

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "Ant Det Finish = %s, Ant Det Number  = %d\n",
		 (board_info->btdm_ant_det_finish ? "Yes" : "No"),
		 board_info->btdm_ant_num_by_ant_det);

	btcoexist->dbg_mode_2ant = false;
	btcoexist->stop_coex_dm = true;
	psd_scan->ant_det_is_ant_det_available = false;

	/* enable BB, REG_SYS_FUNC_EN such that we can write BB Reg correctly */
	u16tmp = btcoexist->btc_read_2byte(btcoexist, 0x2);
	btcoexist->btc_write_2byte(btcoexist, 0x2, u16tmp | BIT(0) | BIT(1));

	/* Local setting bit define */
	/*	BIT0: "0" for no antenna inverse; "1" for antenna inverse  */
	/*	BIT1: "0" for internal switch; "1" for external switch */
	/*	BIT2: "0" for one antenna; "1" for two antenna */
	/* NOTE: here default all internal switch and 1-antenna ==>
	 * BIT1=0 and BIT2=0
	 */

	/* Check efuse 0xc3[6] for Single Antenna Path */

	/* Setup RF front end type */
	halbtc8822b2ant_set_rfe_type(btcoexist);

	/* Set Antenna Path to BT side */
	halbtc8822b2ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO, FORCE_EXEC,
				     BT_8822B_2ANT_PHASE_COEX_POWERON);

	/* Save"single antenna position" info in Local register setting for
	 * FW reading, because FW may not ready at power on
	 */
	if (btcoexist->chip_interface == BTC_INTF_PCI)
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0x3e0, u8tmp);
	else if (btcoexist->chip_interface == BTC_INTF_USB)
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0xfe08, u8tmp);
	else if (btcoexist->chip_interface == BTC_INTF_SDIO)
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0x60, u8tmp);

	/* enable GNT_WL/GNT_BT debug signal to GPIO14/15 */
	halbtc8822b2ant_enable_gnt_to_gpio(btcoexist, true);

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], **********  LTE coex Reg 0x38 (Power-On) = 0x%x**********\n",
		halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x38));

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], **********  MAC Reg 0x70/ BB Reg 0xcb4 (Power-On) = 0x%x / 0x%x\n",
		btcoexist->btc_read_4byte(btcoexist, 0x70),
		btcoexist->btc_read_4byte(btcoexist, 0xcb4));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int interface; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct TYPE_10__ {int tfbga_package; scalar_t__ ant_div_cfg; int /*<<< orphan*/  rfe_type; int /*<<< orphan*/  btdm_ant_pos; } ;
struct TYPE_9__ {int bt_ctrl_agg_buf_size; int agg_buf_size; int increase_scan_dev_num; int miracast_plus_bt; } ;
struct TYPE_8__ {int profile_notified; } ;
struct TYPE_7__ {int /*<<< orphan*/  cnt_bind; } ;
struct btc_coexist {int binded; TYPE_5__ board_info; TYPE_4__ bt_info; TYPE_3__ stack_info; void* adapter; TYPE_2__ statistics; int /*<<< orphan*/  chip_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANTENNA_AT_MAIN_PORT ; 
 int /*<<< orphan*/  BTC_INTF_PCI ; 
 int /*<<< orphan*/  BTC_INTF_UNKNOWN ; 
 int /*<<< orphan*/  BTC_INTF_USB ; 
 int /*<<< orphan*/  BT_COEX_ANT_TYPE_PG ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  INTF_PCI 129 
#define  INTF_USB 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exhalbtc_set_ant_num (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exhalbtc_set_chip_type (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  exhalbtc_set_single_ant_path (struct btc_coexist*,int) ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 
 int rtl_get_hwpg_ant_num (struct rtl_priv*) ; 
 int rtl_get_hwpg_bt_type (struct rtl_priv*) ; 
 int rtl_get_hwpg_package_type (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_get_hwpg_rfe_type (struct rtl_priv*) ; 
 int rtl_get_hwpg_single_ant_path (struct rtl_priv*) ; 

bool exhalbtc_bind_bt_coex_withadapter(void *adapter)
{
	struct rtl_priv *rtlpriv = adapter;
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);
	u8 ant_num = 2, chip_type, single_ant_path = 0;

	if (!btcoexist)
		return false;

	if (btcoexist->binded)
		return false;

	switch (rtlpriv->rtlhal.interface) {
	case INTF_PCI:
		btcoexist->chip_interface = BTC_INTF_PCI;
		break;
	case INTF_USB:
		btcoexist->chip_interface = BTC_INTF_USB;
		break;
	default:
		btcoexist->chip_interface = BTC_INTF_UNKNOWN;
		break;
	}

	btcoexist->binded = true;
	btcoexist->statistics.cnt_bind++;

	btcoexist->adapter = adapter;

	btcoexist->stack_info.profile_notified = false;

	btcoexist->bt_info.bt_ctrl_agg_buf_size = false;
	btcoexist->bt_info.agg_buf_size = 5;

	btcoexist->bt_info.increase_scan_dev_num = false;
	btcoexist->bt_info.miracast_plus_bt = false;

	chip_type = rtl_get_hwpg_bt_type(rtlpriv);
	exhalbtc_set_chip_type(btcoexist, chip_type);
	ant_num = rtl_get_hwpg_ant_num(rtlpriv);
	exhalbtc_set_ant_num(rtlpriv, BT_COEX_ANT_TYPE_PG, ant_num);

	/* set default antenna position to main  port */
	btcoexist->board_info.btdm_ant_pos = BTC_ANTENNA_AT_MAIN_PORT;

	single_ant_path = rtl_get_hwpg_single_ant_path(rtlpriv);
	exhalbtc_set_single_ant_path(btcoexist, single_ant_path);

	if (rtl_get_hwpg_package_type(rtlpriv) == 0)
		btcoexist->board_info.tfbga_package = false;
	else if (rtl_get_hwpg_package_type(rtlpriv) == 1)
		btcoexist->board_info.tfbga_package = false;
	else
		btcoexist->board_info.tfbga_package = true;

	if (btcoexist->board_info.tfbga_package)
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Package Type = TFBGA\n");
	else
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Package Type = Non-TFBGA\n");

	btcoexist->board_info.rfe_type = rtl_get_hwpg_rfe_type(rtlpriv);
	btcoexist->board_info.ant_div_cfg = 0;

	return true;
}
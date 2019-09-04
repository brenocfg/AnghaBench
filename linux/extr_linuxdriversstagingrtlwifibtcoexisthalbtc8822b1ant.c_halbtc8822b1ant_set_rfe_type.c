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
struct btc_board_info {int rfe_type; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;struct btc_board_info board_info; } ;
struct TYPE_2__ {int rfe_module_type; int ext_ant_switch_exist; void* ext_ant_switch_type; scalar_t__ ext_ant_switch_ctrl_polarity; } ;

/* Variables and functions */
 void* BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT ; 
 TYPE_1__* rfe_type ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b1ant_set_rfe_type(struct btc_coexist *btcoexist)
{
	struct btc_board_info *board_info = &btcoexist->board_info;

	/* Ext switch buffer mux */
	btcoexist->btc_write_1byte(btcoexist, 0x974, 0xff);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x1991, 0x3, 0x0);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbe, 0x8, 0x0);

	/* the following setup should be got from Efuse in the future */
	rfe_type->rfe_module_type = board_info->rfe_type;

	rfe_type->ext_ant_switch_ctrl_polarity = 0;

	switch (rfe_type->rfe_module_type) {
	case 0:
	default:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 1:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 2:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 3:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 4:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 5:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 6:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	case 7:
		rfe_type->ext_ant_switch_exist = true;
		rfe_type->ext_ant_switch_type =
			BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT;
		break;
	}
}
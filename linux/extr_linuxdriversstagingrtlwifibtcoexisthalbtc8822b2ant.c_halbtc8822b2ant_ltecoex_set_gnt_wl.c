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
typedef  int u32 ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
#define  BT_8822B_2ANT_GNT_BLOCK_BB 130 
#define  BT_8822B_2ANT_GNT_BLOCK_RFC 129 
#define  BT_8822B_2ANT_GNT_BLOCK_RFC_BB 128 
 int /*<<< orphan*/  halbtc8822b2ant_ltecoex_indirect_write_reg (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b2ant_ltecoex_set_gnt_wl(struct btc_coexist *btcoexist,
					       u8 control_block,
					       bool sw_control, u8 state)
{
	u32 val = 0, bit_mask;

	state = state & 0x1;
	val = (sw_control) ? ((state << 1) | 0x1) : 0;

	switch (control_block) {
	case BT_8822B_2ANT_GNT_BLOCK_RFC_BB:
	default:
		bit_mask = 0x3000;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[13:12] */
		bit_mask = 0x0300;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[9:8] */
		break;
	case BT_8822B_2ANT_GNT_BLOCK_RFC:
		bit_mask = 0x3000;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[13:12] */
		break;
	case BT_8822B_2ANT_GNT_BLOCK_BB:
		bit_mask = 0x0300;
		halbtc8822b2ant_ltecoex_indirect_write_reg(
			btcoexist, 0x38, bit_mask, val); /* 0x38[9:8] */
		break;
	}
}
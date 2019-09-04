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
struct btc_coexist {int dummy; } ;

/* Variables and functions */
#define  BT_8822B_1ANT_CTT_BT_VS_LTE 129 
#define  BT_8822B_1ANT_CTT_WL_VS_LTE 128 
 int /*<<< orphan*/  halbtc8822b1ant_ltecoex_indirect_write_reg (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void
halbtc8822b1ant_ltecoex_set_coex_table(struct btc_coexist *btcoexist,
				       u8 table_type, u16 table_content)
{
	u16 reg_addr = 0x0000;

	switch (table_type) {
	case BT_8822B_1ANT_CTT_WL_VS_LTE:
		reg_addr = 0xa0;
		break;
	case BT_8822B_1ANT_CTT_BT_VS_LTE:
		reg_addr = 0xa4;
		break;
	}

	if (reg_addr != 0x0000)
		halbtc8822b1ant_ltecoex_indirect_write_reg(
			btcoexist, reg_addr, 0xffff,
			table_content); /* 0xa0[15:0] or 0xa4[15:0] */
}
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
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc8822b1ant_ltecoex_indirect_write_reg (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b1ant_ltecoex_enable(struct btc_coexist *btcoexist,
					   bool enable)
{
	u8 val;

	val = (enable) ? 1 : 0;
	/* 0x38[7] */
	halbtc8822b1ant_ltecoex_indirect_write_reg(btcoexist, 0x38, 0x80, val);
}
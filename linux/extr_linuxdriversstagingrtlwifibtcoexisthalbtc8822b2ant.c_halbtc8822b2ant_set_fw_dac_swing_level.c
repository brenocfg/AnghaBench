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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
halbtc8822b2ant_set_fw_dac_swing_level(struct btc_coexist *btcoexist,
				       u8 dac_swing_lvl)
{
	u8 h2c_parameter[1] = {0};
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	/* There are several type of dacswing */
	/* 0x18/ 0x10/ 0xc/ 0x8/ 0x4/ 0x6 */
	h2c_parameter[0] = dac_swing_lvl;

	btcoexist->btc_fill_h2c(btcoexist, 0x64, 1, h2c_parameter);
}
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

__attribute__((used)) static void halbtc8822b2ant_set_fw_dec_bt_pwr(struct btc_coexist *btcoexist,
					      u8 dec_bt_pwr_lvl)
{
	u32 RTL97F_8822B = 0;
	u8 h2c_parameter[1] = {0};

	if (RTL97F_8822B)
		return;

	h2c_parameter[0] = dec_bt_pwr_lvl;

	btcoexist->btc_fill_h2c(btcoexist, 0x62, 1, h2c_parameter);
}
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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct btc_coexist {int dummy; } ;
struct TYPE_2__ {scalar_t__ cur_fw_dac_swing_lvl; scalar_t__ pre_fw_dac_swing_lvl; } ;

/* Variables and functions */
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_fw_dac_swing_level (struct btc_coexist*,scalar_t__) ; 

__attribute__((used)) static void halbtc8822b2ant_fw_dac_swing_lvl(struct btc_coexist *btcoexist,
					     bool force_exec,
					     u8 fw_dac_swing_lvl)
{
	u32 RTL97F_8822B = 0;

	if (RTL97F_8822B)
		return;

	coex_dm->cur_fw_dac_swing_lvl = fw_dac_swing_lvl;

	if (!force_exec) {
		if (coex_dm->pre_fw_dac_swing_lvl ==
		    coex_dm->cur_fw_dac_swing_lvl)
			return;
	}

	halbtc8822b2ant_set_fw_dac_swing_level(btcoexist,
					       coex_dm->cur_fw_dac_swing_lvl);

	coex_dm->pre_fw_dac_swing_lvl = coex_dm->cur_fw_dac_swing_lvl;
}
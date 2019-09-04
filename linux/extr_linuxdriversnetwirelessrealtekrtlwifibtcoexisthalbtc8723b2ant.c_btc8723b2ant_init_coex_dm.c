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
struct btc_coexist {int dummy; } ;
struct TYPE_2__ {scalar_t__ pop_event_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8723b2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8723b2ant_dec_bt_pwr (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8723b2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8723b2ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8723b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8723b2ant_sw_mechanism (struct btc_coexist*,int,int,int,int) ; 
 TYPE_1__* coex_sta ; 

__attribute__((used)) static void btc8723b2ant_init_coex_dm(struct btc_coexist *btcoexist)
{
	/* force to reset coex mechanism*/
	btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	btc8723b2ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	btc8723b2ant_ps_tdma(btcoexist, FORCE_EXEC, false, 1);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 6);
	btc8723b2ant_dec_bt_pwr(btcoexist, FORCE_EXEC, 0);

	btc8723b2ant_sw_mechanism(btcoexist, false, false, false, false);

	coex_sta->pop_event_cnt = 0;
}
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
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8192e2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8192e2ant_dec_bt_pwr (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8192e2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_sw_mechanism1 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_sw_mechanism2 (struct btc_coexist*,int,int,int,int) ; 

__attribute__((used)) static void btc8192e2ant_coex_all_off(struct btc_coexist *btcoexist)
{
	/* fw all off */
	btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
	btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	/* sw all off */
	btc8192e2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8192e2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);

	/* hw all off */
	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
}
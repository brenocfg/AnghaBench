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
 int /*<<< orphan*/  halbtc8822b2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
halbtc8822b2ant_action_wifi_multi_port(struct btc_coexist *btcoexist)
{
	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);

	/* hw all off */
	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
}
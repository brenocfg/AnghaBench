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
struct btc_bt_link_info {scalar_t__ a2dp_exist; scalar_t__ pan_exist; } ;
struct btc_coexist {struct btc_bt_link_info bt_link_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8822b2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
halbtc8822b2ant_action_wifi_link_process(struct btc_coexist *btcoexist)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 0xd4);

	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);

	if (bt_link_info->pan_exist) {
		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);

	} else if (bt_link_info->a2dp_exist) {
		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 16);

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);
	} else {
		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 21);

		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);
	}
}
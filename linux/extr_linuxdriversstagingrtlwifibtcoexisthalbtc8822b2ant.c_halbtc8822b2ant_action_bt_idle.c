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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_2__ {scalar_t__ bt_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 scalar_t__ BT_8822B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  halbtc8822b2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8822b2ant_action_bt_idle(struct btc_coexist *btcoexist)
{
	bool wifi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	if (!wifi_busy) {
		halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);

		halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
	} else { /* if wl busy */

		if (BT_8822B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		    coex_dm->bt_status) {
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 0);

			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false,
						0);
		} else {
			halbtc8822b2ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 8);
			halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						12);
		}
	}

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 0xd8);
}
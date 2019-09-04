#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int btdm_ant_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt_power_on; } ;
struct btc_coexist {TYPE_2__ board_info; int /*<<< orphan*/  adapter; TYPE_1__ statistics; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8723B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_btc8723b1ant_power_on_setting (struct btc_coexist*) ; 
 int /*<<< orphan*/  ex_btc8723b2ant_power_on_setting (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 

void exhalbtc_power_on_setting(struct btc_coexist *btcoexist)
{
	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;

	btcoexist->statistics.cnt_power_on++;

	if (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_power_on_setting(btcoexist);
		else if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_power_on_setting(btcoexist);
	}
}
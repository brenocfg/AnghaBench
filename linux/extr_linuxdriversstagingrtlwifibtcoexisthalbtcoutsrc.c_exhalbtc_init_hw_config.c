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
struct TYPE_3__ {int /*<<< orphan*/  cnt_init_hw_config; } ;
struct btc_coexist {TYPE_2__ board_info; int /*<<< orphan*/  adapter; TYPE_1__ statistics; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8822B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_btc8822b1ant_init_hw_config (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  ex_btc8822b2ant_init_hw_config (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_send_wifi_port_id_cmd (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_set_default_port_id_cmd (struct btc_coexist*) ; 

void exhalbtc_init_hw_config(struct btc_coexist *btcoexist, bool wifi_only)
{
	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;

	btcoexist->statistics.cnt_init_hw_config++;

	if (IS_HARDWARE_TYPE_8822B(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8822b1ant_init_hw_config(btcoexist, wifi_only);
		else if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8822b2ant_init_hw_config(btcoexist, wifi_only);

		halbtc_set_default_port_id_cmd(btcoexist);
		halbtc_send_wifi_port_id_cmd(btcoexist);
	}
}
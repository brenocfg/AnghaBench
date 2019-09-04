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
struct TYPE_2__ {int cur_ignore_wlan_act; int pre_ignore_wlan_act; } ;

/* Variables and functions */
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_fw_ignore_wlan_act (struct btc_coexist*,int) ; 

__attribute__((used)) static void halbtc8822b1ant_ignore_wlan_act(struct btc_coexist *btcoexist,
					    bool force_exec, bool enable)
{
	coex_dm->cur_ignore_wlan_act = enable;

	if (!force_exec) {
		if (coex_dm->pre_ignore_wlan_act ==
		    coex_dm->cur_ignore_wlan_act) {
			coex_dm->pre_ignore_wlan_act =
				coex_dm->cur_ignore_wlan_act;
			return;
		}
	}

	halbtc8822b1ant_set_fw_ignore_wlan_act(btcoexist, enable);

	coex_dm->pre_ignore_wlan_act = coex_dm->cur_ignore_wlan_act;
}
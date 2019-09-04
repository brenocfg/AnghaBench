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
typedef  void* u16 ;
struct TYPE_2__ {void* bt_hci_ver; void* bt_real_fw_ver; } ;
struct btc_coexist {TYPE_1__ bt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 

void exhalbtc_set_bt_patch_version(struct btc_coexist *btcoexist,
				   u16 bt_hci_version, u16 bt_patch_version)
{
	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;

	btcoexist->bt_info.bt_real_fw_ver = bt_patch_version;
	btcoexist->bt_info.bt_hci_ver = bt_hci_version;
}
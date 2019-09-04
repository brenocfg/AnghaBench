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

/* Variables and functions */
 scalar_t__ rtnl_is_locked () ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wilc_wfi_mon ; 

int wilc_wfi_deinit_mon_interface(void)
{
	bool rollback_lock = false;

	if (wilc_wfi_mon) {
		if (rtnl_is_locked()) {
			rtnl_unlock();
			rollback_lock = true;
		}
		unregister_netdev(wilc_wfi_mon);

		if (rollback_lock) {
			rtnl_lock();
			rollback_lock = false;
		}
		wilc_wfi_mon = NULL;
	}
	return 0;
}
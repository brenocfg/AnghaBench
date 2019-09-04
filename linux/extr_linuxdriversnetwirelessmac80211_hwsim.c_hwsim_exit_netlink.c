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
 int /*<<< orphan*/  genl_unregister_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwsim_genl_family ; 
 int /*<<< orphan*/  hwsim_netlink_notifier ; 
 int /*<<< orphan*/  netlink_unregister_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hwsim_exit_netlink(void)
{
	/* unregister the notifier */
	netlink_unregister_notifier(&hwsim_netlink_notifier);
	/* unregister the family */
	genl_unregister_family(&hwsim_genl_family);
}
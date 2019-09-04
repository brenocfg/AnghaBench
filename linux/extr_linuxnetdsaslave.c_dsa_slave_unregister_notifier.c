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
 int /*<<< orphan*/  dsa_slave_nb ; 
 int /*<<< orphan*/  dsa_slave_switchdev_notifier ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int unregister_switchdev_notifier (int /*<<< orphan*/ *) ; 

void dsa_slave_unregister_notifier(void)
{
	int err;

	err = unregister_switchdev_notifier(&dsa_slave_switchdev_notifier);
	if (err)
		pr_err("DSA: failed to unregister switchdev notifier (%d)\n", err);

	err = unregister_netdevice_notifier(&dsa_slave_nb);
	if (err)
		pr_err("DSA: failed to unregister slave notifier (%d)\n", err);
}
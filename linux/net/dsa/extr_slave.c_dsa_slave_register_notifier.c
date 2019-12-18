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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_slave_nb ; 
 struct notifier_block dsa_slave_switchdev_blocking_notifier ; 
 int /*<<< orphan*/  dsa_slave_switchdev_notifier ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int register_switchdev_blocking_notifier (struct notifier_block*) ; 
 int register_switchdev_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_switchdev_notifier (int /*<<< orphan*/ *) ; 

int dsa_slave_register_notifier(void)
{
	struct notifier_block *nb;
	int err;

	err = register_netdevice_notifier(&dsa_slave_nb);
	if (err)
		return err;

	err = register_switchdev_notifier(&dsa_slave_switchdev_notifier);
	if (err)
		goto err_switchdev_nb;

	nb = &dsa_slave_switchdev_blocking_notifier;
	err = register_switchdev_blocking_notifier(nb);
	if (err)
		goto err_switchdev_blocking_nb;

	return 0;

err_switchdev_blocking_nb:
	unregister_switchdev_notifier(&dsa_slave_switchdev_notifier);
err_switchdev_nb:
	unregister_netdevice_notifier(&dsa_slave_nb);
	return err;
}
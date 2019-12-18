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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct net_device {int /*<<< orphan*/ * dsa_ptr; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_group ; 
 int /*<<< orphan*/  dsa_master_ethtool_teardown (struct net_device*) ; 
 int /*<<< orphan*/  dsa_master_ndo_teardown (struct net_device*) ; 
 int /*<<< orphan*/  dsa_master_reset_mtu (struct net_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

void dsa_master_teardown(struct net_device *dev)
{
	sysfs_remove_group(&dev->dev.kobj, &dsa_group);
	dsa_master_ndo_teardown(dev);
	dsa_master_ethtool_teardown(dev);
	dsa_master_reset_mtu(dev);

	dev->dsa_ptr = NULL;

	/* If we used a tagging format that doesn't have an ethertype
	 * field, make sure that all packets from this point get sent
	 * without the tag and go through the regular receive path.
	 */
	wmb();
}
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
struct net_device {TYPE_1__ dev; struct dsa_port* dsa_ptr; } ;
struct dsa_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_group ; 
 int dsa_master_ethtool_setup (struct net_device*) ; 
 int /*<<< orphan*/  dsa_master_ethtool_teardown (struct net_device*) ; 
 int dsa_master_ndo_setup (struct net_device*) ; 
 int /*<<< orphan*/  dsa_master_ndo_teardown (struct net_device*) ; 
 int /*<<< orphan*/  dsa_master_set_mtu (struct net_device*,struct dsa_port*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

int dsa_master_setup(struct net_device *dev, struct dsa_port *cpu_dp)
{
	int ret;

	dsa_master_set_mtu(dev,  cpu_dp);

	/* If we use a tagging format that doesn't have an ethertype
	 * field, make sure that all packets from this point on get
	 * sent to the tag format's receive function.
	 */
	wmb();

	dev->dsa_ptr = cpu_dp;
	ret = dsa_master_ethtool_setup(dev);
	if (ret)
		return ret;

	ret = dsa_master_ndo_setup(dev);
	if (ret)
		goto out_err_ethtool_teardown;

	ret = sysfs_create_group(&dev->dev.kobj, &dsa_group);
	if (ret)
		goto out_err_ndo_teardown;

	return ret;

out_err_ndo_teardown:
	dsa_master_ndo_teardown(dev);
out_err_ethtool_teardown:
	dsa_master_ethtool_teardown(dev);
	return ret;
}
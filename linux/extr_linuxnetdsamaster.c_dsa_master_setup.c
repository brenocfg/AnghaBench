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
struct net_device {int /*<<< orphan*/  addr_list_lock; struct dsa_port* dsa_ptr; } ;
struct dsa_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_master_addr_list_lock_key ; 
 int dsa_master_ethtool_setup (struct net_device*) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

int dsa_master_setup(struct net_device *dev, struct dsa_port *cpu_dp)
{
	/* If we use a tagging format that doesn't have an ethertype
	 * field, make sure that all packets from this point on get
	 * sent to the tag format's receive function.
	 */
	wmb();

	dev->dsa_ptr = cpu_dp;
	lockdep_set_class(&dev->addr_list_lock,
			  &dsa_master_addr_list_lock_key);

	return dsa_master_ethtool_setup(dev);
}
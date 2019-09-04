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
struct phy_dev {struct net_device** dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int MAX_NIC_TYPE ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void unregister_lte_device(struct phy_dev *phy_dev)
{
	struct net_device *net;
	int index;

	for (index = 0; index < MAX_NIC_TYPE; index++) {
		net = phy_dev->dev[index];
		if (!net)
			continue;

		unregister_netdev(net);
		free_netdev(net);
	}
}
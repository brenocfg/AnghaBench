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
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

int xlgmac_drv_remove(struct device *dev)
{
	struct net_device *netdev = dev_get_drvdata(dev);

	unregister_netdev(netdev);
	free_netdev(netdev);

	return 0;
}
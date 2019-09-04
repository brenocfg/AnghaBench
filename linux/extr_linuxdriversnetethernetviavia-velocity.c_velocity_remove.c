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
struct velocity_info {int /*<<< orphan*/  mac_regs; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  velocity_nics ; 

__attribute__((used)) static int velocity_remove(struct device *dev)
{
	struct net_device *netdev = dev_get_drvdata(dev);
	struct velocity_info *vptr = netdev_priv(netdev);

	unregister_netdev(netdev);
	netif_napi_del(&vptr->napi);
	iounmap(vptr->mac_regs);
	free_netdev(netdev);
	velocity_nics--;

	return 0;
}
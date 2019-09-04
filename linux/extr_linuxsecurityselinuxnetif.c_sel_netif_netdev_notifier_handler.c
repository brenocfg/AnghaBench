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
struct net_device {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  sel_netif_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sel_netif_netdev_notifier_handler(struct notifier_block *this,
					     unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	if (event == NETDEV_DOWN)
		sel_netif_kill(dev_net(dev), dev->ifindex);

	return NOTIFY_DONE;
}
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
struct netdev_notifier_change_info {int flags_changed; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int IFF_NOARP ; 
#define  NETDEV_CHANGE 129 
#define  NETDEV_CHANGEADDR 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  arp_tbl ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  neigh_carrier_down (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_changeaddr (int /*<<< orphan*/ *,struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  rt_cache_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arp_netdev_event(struct notifier_block *this, unsigned long event,
			    void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct netdev_notifier_change_info *change_info;

	switch (event) {
	case NETDEV_CHANGEADDR:
		neigh_changeaddr(&arp_tbl, dev);
		rt_cache_flush(dev_net(dev));
		break;
	case NETDEV_CHANGE:
		change_info = ptr;
		if (change_info->flags_changed & IFF_NOARP)
			neigh_changeaddr(&arp_tbl, dev);
		if (!netif_carrier_ok(dev))
			neigh_carrier_down(&arp_tbl, dev);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}
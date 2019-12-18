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
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGE 133 
#define  NETDEV_CHANGENAME 132 
#define  NETDEV_DOWN 131 
#define  NETDEV_REGISTER 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int failover_slave_link_change (struct net_device*) ; 
 int failover_slave_name_change (struct net_device*) ; 
 int failover_slave_register (struct net_device*) ; 
 int failover_slave_unregister (struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 scalar_t__ netif_is_failover (struct net_device*) ; 

__attribute__((used)) static int
failover_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *event_dev = netdev_notifier_info_to_dev(ptr);

	/* Skip parent events */
	if (netif_is_failover(event_dev))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_REGISTER:
		return failover_slave_register(event_dev);
	case NETDEV_UNREGISTER:
		return failover_slave_unregister(event_dev);
	case NETDEV_UP:
	case NETDEV_DOWN:
	case NETDEV_CHANGE:
		return failover_slave_link_change(event_dev);
	case NETDEV_CHANGENAME:
		return failover_slave_name_change(event_dev);
	default:
		return NOTIFY_DONE;
	}
}
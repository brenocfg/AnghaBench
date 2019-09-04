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
struct net_device {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_PHONET ; 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UNREGISTER 128 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  phonet_device_autoconf (struct net_device*) ; 
 int /*<<< orphan*/  phonet_device_destroy (struct net_device*) ; 
 int /*<<< orphan*/  phonet_route_autodel (struct net_device*) ; 

__attribute__((used)) static int phonet_device_notify(struct notifier_block *me, unsigned long what,
				void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	switch (what) {
	case NETDEV_REGISTER:
		if (dev->type == ARPHRD_PHONET)
			phonet_device_autoconf(dev);
		break;
	case NETDEV_UNREGISTER:
		phonet_device_destroy(dev);
		phonet_route_autodel(dev);
		break;
	}
	return 0;

}
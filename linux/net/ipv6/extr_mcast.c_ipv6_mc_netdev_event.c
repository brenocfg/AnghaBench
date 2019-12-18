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
struct inet6_dev {int dummy; } ;

/* Variables and functions */
#define  NETDEV_RESEND_IGMP 128 
 int NOTIFY_DONE ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  ipv6_mc_rejoin_groups (struct inet6_dev*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int ipv6_mc_netdev_event(struct notifier_block *this,
				unsigned long event,
				void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct inet6_dev *idev = __in6_dev_get(dev);

	switch (event) {
	case NETDEV_RESEND_IGMP:
		if (idev)
			ipv6_mc_rejoin_groups(idev);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}
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
struct netlink_ext_ack {int dummy; } ;
struct netdev_notifier_info {struct netlink_ext_ack* extack; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int call_netdevice_notifiers_info (unsigned long,struct netdev_notifier_info*) ; 

__attribute__((used)) static int call_netdevice_notifiers_extack(unsigned long val,
					   struct net_device *dev,
					   struct netlink_ext_ack *extack)
{
	struct netdev_notifier_info info = {
		.dev = dev,
		.extack = extack,
	};

	return call_netdevice_notifiers_info(val, &info);
}
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
struct netdev_notifier_info {struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int call_netdevice_notifiers_info (unsigned long,struct netdev_notifier_info*) ; 

int call_netdevice_notifiers(unsigned long val, struct net_device *dev)
{
	struct netdev_notifier_info info = {
		.dev = dev,
	};

	return call_netdevice_notifiers_info(val, &info);
}
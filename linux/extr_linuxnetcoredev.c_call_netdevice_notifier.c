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
struct notifier_block {int (* notifier_call ) (struct notifier_block*,unsigned long,struct netdev_notifier_info*) ;} ;
struct netdev_notifier_info {struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int stub1 (struct notifier_block*,unsigned long,struct netdev_notifier_info*) ; 

__attribute__((used)) static int call_netdevice_notifier(struct notifier_block *nb, unsigned long val,
				   struct net_device *dev)
{
	struct netdev_notifier_info info = {
		.dev = dev,
	};

	return nb->notifier_call(nb, val, &info);
}
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
struct switchdev_notifier_info {struct netlink_ext_ack* extack; struct net_device* dev; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int atomic_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,struct switchdev_notifier_info*) ; 
 int /*<<< orphan*/  switchdev_notif_chain ; 

int call_switchdev_notifiers(unsigned long val, struct net_device *dev,
			     struct switchdev_notifier_info *info,
			     struct netlink_ext_ack *extack)
{
	info->dev = dev;
	info->extack = extack;
	return atomic_notifier_call_chain(&switchdev_notif_chain, val, info);
}
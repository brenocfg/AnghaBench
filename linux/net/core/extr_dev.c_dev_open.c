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
struct net_device {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NETDEV_UP ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int __dev_open (struct net_device*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rtmsg_ifinfo (int /*<<< orphan*/ ,struct net_device*,int,int /*<<< orphan*/ ) ; 

int dev_open(struct net_device *dev, struct netlink_ext_ack *extack)
{
	int ret;

	if (dev->flags & IFF_UP)
		return 0;

	ret = __dev_open(dev, extack);
	if (ret < 0)
		return ret;

	rtmsg_ifinfo(RTM_NEWLINK, dev, IFF_UP|IFF_RUNNING, GFP_KERNEL);
	call_netdevice_notifiers(NETDEV_UP, dev);

	return ret;
}
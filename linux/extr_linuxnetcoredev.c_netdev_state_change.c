#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct net_device* dev; } ;
struct netdev_notifier_change_info {TYPE_1__ info; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NETDEV_CHANGE ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  call_netdevice_notifiers_info (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rtmsg_ifinfo (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void netdev_state_change(struct net_device *dev)
{
	if (dev->flags & IFF_UP) {
		struct netdev_notifier_change_info change_info = {
			.info.dev = dev,
		};

		call_netdevice_notifiers_info(NETDEV_CHANGE,
					      &change_info.info);
		rtmsg_ifinfo(RTM_NEWLINK, dev, 0, GFP_KERNEL);
	}
}
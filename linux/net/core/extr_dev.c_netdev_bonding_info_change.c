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
struct netdev_notifier_bonding_info {TYPE_1__ info; int /*<<< orphan*/  bonding_info; } ;
struct netdev_bonding_info {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_BONDING_INFO ; 
 int /*<<< orphan*/  call_netdevice_notifiers_info (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct netdev_bonding_info*,int) ; 

void netdev_bonding_info_change(struct net_device *dev,
				struct netdev_bonding_info *bonding_info)
{
	struct netdev_notifier_bonding_info info = {
		.info.dev = dev,
	};

	memcpy(&info.bonding_info, bonding_info,
	       sizeof(struct netdev_bonding_info));
	call_netdevice_notifiers_info(NETDEV_BONDING_INFO,
				      &info.info);
}
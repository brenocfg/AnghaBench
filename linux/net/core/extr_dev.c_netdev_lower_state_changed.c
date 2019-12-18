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
struct netdev_notifier_changelowerstate_info {TYPE_1__ info; void* lower_state_info; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  NETDEV_CHANGELOWERSTATE ; 
 int /*<<< orphan*/  call_netdevice_notifiers_info (int /*<<< orphan*/ ,TYPE_1__*) ; 

void netdev_lower_state_changed(struct net_device *lower_dev,
				void *lower_state_info)
{
	struct netdev_notifier_changelowerstate_info changelowerstate_info = {
		.info.dev = lower_dev,
	};

	ASSERT_RTNL();
	changelowerstate_info.lower_state_info = lower_state_info;
	call_netdevice_notifiers_info(NETDEV_CHANGELOWERSTATE,
				      &changelowerstate_info.info);
}
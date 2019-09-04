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
struct netdev_notifier_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  netdev_chain ; 
 int raw_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,struct netdev_notifier_info*) ; 

__attribute__((used)) static int call_netdevice_notifiers_info(unsigned long val,
					 struct netdev_notifier_info *info)
{
	ASSERT_RTNL();
	return raw_notifier_call_chain(&netdev_chain, val, info);
}
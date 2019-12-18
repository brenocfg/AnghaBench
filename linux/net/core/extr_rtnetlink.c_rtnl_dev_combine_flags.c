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
struct net_device {int dummy; } ;
struct ifinfomsg {unsigned int ifi_flags; int ifi_change; } ;

/* Variables and functions */
 unsigned int rtnl_dev_get_flags (struct net_device const*) ; 

__attribute__((used)) static unsigned int rtnl_dev_combine_flags(const struct net_device *dev,
					   const struct ifinfomsg *ifm)
{
	unsigned int flags = ifm->ifi_flags;

	/* bugwards compatibility: ifi_change == 0 is treated as ~0 */
	if (ifm->ifi_change)
		flags = (flags & ifm->ifi_change) |
			(rtnl_dev_get_flags(dev) & ~ifm->ifi_change);

	return flags;
}
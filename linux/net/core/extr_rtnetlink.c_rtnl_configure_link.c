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
struct net_device {unsigned int flags; scalar_t__ rtnl_link_state; } ;
struct ifinfomsg {scalar_t__ ifi_change; scalar_t__ ifi_flags; } ;

/* Variables and functions */
 scalar_t__ RTNL_LINK_INITIALIZED ; 
 int __dev_change_flags (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dev_notify_flags (struct net_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rtnl_dev_combine_flags (struct net_device*,struct ifinfomsg const*) ; 

int rtnl_configure_link(struct net_device *dev, const struct ifinfomsg *ifm)
{
	unsigned int old_flags;
	int err;

	old_flags = dev->flags;
	if (ifm && (ifm->ifi_flags || ifm->ifi_change)) {
		err = __dev_change_flags(dev, rtnl_dev_combine_flags(dev, ifm),
					 NULL);
		if (err < 0)
			return err;
	}

	if (dev->rtnl_link_state == RTNL_LINK_INITIALIZED) {
		__dev_notify_flags(dev, old_flags, (old_flags ^ dev->flags));
	} else {
		dev->rtnl_link_state = RTNL_LINK_INITIALIZED;
		__dev_notify_flags(dev, old_flags, ~0U);
	}
	return 0;
}
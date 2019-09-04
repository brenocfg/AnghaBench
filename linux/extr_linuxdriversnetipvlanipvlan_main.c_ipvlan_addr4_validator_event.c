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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct ipvl_dev {int /*<<< orphan*/  port; } ;
struct in_validator_info {int /*<<< orphan*/  extack; int /*<<< orphan*/  ivi_addr; TYPE_1__* ivi_dev; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EADDRINUSE ; 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  NL_SET_ERR_MSG (int /*<<< orphan*/ ,char*) ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  ipvlan_addr_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipvlan_is_valid_dev (struct net_device*) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 
 int notifier_from_errno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipvlan_addr4_validator_event(struct notifier_block *unused,
					unsigned long event, void *ptr)
{
	struct in_validator_info *ivi = (struct in_validator_info *)ptr;
	struct net_device *dev = (struct net_device *)ivi->ivi_dev->dev;
	struct ipvl_dev *ipvlan = netdev_priv(dev);

	if (!ipvlan_is_valid_dev(dev))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		if (ipvlan_addr_busy(ipvlan->port, &ivi->ivi_addr, false)) {
			NL_SET_ERR_MSG(ivi->extack,
				       "Address already assigned to an ipvlan device");
			return notifier_from_errno(-EADDRINUSE);
		}
		break;
	}

	return NOTIFY_OK;
}
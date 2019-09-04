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
struct pktgen_net {scalar_t__ pktgen_exiting; } ;
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  NETDEV_CHANGENAME 129 
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct pktgen_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  pg_net_id ; 
 int /*<<< orphan*/  pktgen_change_name (struct pktgen_net*,struct net_device*) ; 
 int /*<<< orphan*/  pktgen_mark_device (struct pktgen_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pktgen_device_event(struct notifier_block *unused,
			       unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct pktgen_net *pn = net_generic(dev_net(dev), pg_net_id);

	if (pn->pktgen_exiting)
		return NOTIFY_DONE;

	/* It is OK that we do not hold the group lock right now,
	 * as we run under the RTNL lock.
	 */

	switch (event) {
	case NETDEV_CHANGENAME:
		pktgen_change_name(pn, dev);
		break;

	case NETDEV_UNREGISTER:
		pktgen_mark_device(pn, dev->name);
		break;
	}

	return NOTIFY_DONE;
}
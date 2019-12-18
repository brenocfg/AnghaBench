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
struct wpan_dev {int /*<<< orphan*/  list; int /*<<< orphan*/  iftype; struct net_device* netdev; int /*<<< orphan*/  identifier; int /*<<< orphan*/  wpan_phy; } ;
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  features; struct wpan_dev* ieee802154_ptr; } ;
struct cfg802154_registered_device {int /*<<< orphan*/  devlist_generation; int /*<<< orphan*/  opencount; int /*<<< orphan*/  dev_wait; int /*<<< orphan*/  wpan_dev_list; int /*<<< orphan*/  wpan_dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  NETDEV_DOWN 131 
#define  NETDEV_REGISTER 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  cfg802154_update_iface_num (struct cfg802154_registered_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 struct cfg802154_registered_device* wpan_phy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg802154_netdev_notifier_call(struct notifier_block *nb,
					  unsigned long state, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct wpan_dev *wpan_dev = dev->ieee802154_ptr;
	struct cfg802154_registered_device *rdev;

	if (!wpan_dev)
		return NOTIFY_DONE;

	rdev = wpan_phy_to_rdev(wpan_dev->wpan_phy);

	/* TODO WARN_ON unspec type */

	switch (state) {
		/* TODO NETDEV_DEVTYPE */
	case NETDEV_REGISTER:
		dev->features |= NETIF_F_NETNS_LOCAL;
		wpan_dev->identifier = ++rdev->wpan_dev_id;
		list_add_rcu(&wpan_dev->list, &rdev->wpan_dev_list);
		rdev->devlist_generation++;

		wpan_dev->netdev = dev;
		break;
	case NETDEV_DOWN:
		cfg802154_update_iface_num(rdev, wpan_dev->iftype, -1);

		rdev->opencount--;
		wake_up(&rdev->dev_wait);
		break;
	case NETDEV_UP:
		cfg802154_update_iface_num(rdev, wpan_dev->iftype, 1);

		rdev->opencount++;
		break;
	case NETDEV_UNREGISTER:
		/* It is possible to get NETDEV_UNREGISTER
		 * multiple times. To detect that, check
		 * that the interface is still on the list
		 * of registered interfaces, and only then
		 * remove and clean it up.
		 */
		if (!list_empty(&wpan_dev->list)) {
			list_del_rcu(&wpan_dev->list);
			rdev->devlist_generation++;
		}
		/* synchronize (so that we won't find this netdev
		 * from other code any more) and then clear the list
		 * head so that the above code can safely check for
		 * !list_empty() to avoid double-cleanup.
		 */
		synchronize_rcu();
		INIT_LIST_HEAD(&wpan_dev->list);
		break;
	default:
		return NOTIFY_DONE;
	}

	return NOTIFY_OK;
}
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
struct wpan_phy {int /*<<< orphan*/  dev; } ;
struct cfg802154_registered_device {int opencount; int /*<<< orphan*/  list; int /*<<< orphan*/  wpan_dev_list; int /*<<< orphan*/  dev_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cfg802154_rdev_list_generation ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cfg802154_registered_device* wpan_phy_to_rdev (struct wpan_phy*) ; 

void wpan_phy_unregister(struct wpan_phy *phy)
{
	struct cfg802154_registered_device *rdev = wpan_phy_to_rdev(phy);

	wait_event(rdev->dev_wait, ({
		int __count;
		rtnl_lock();
		__count = rdev->opencount;
		rtnl_unlock();
		__count == 0; }));

	rtnl_lock();
	/* TODO nl802154 phy notify */
	/* TODO phy registered lock */

	WARN_ON(!list_empty(&rdev->wpan_dev_list));

	/* First remove the hardware from everywhere, this makes
	 * it impossible to find from userspace.
	 */
	list_del_rcu(&rdev->list);
	synchronize_rcu();

	cfg802154_rdev_list_generation++;

	device_del(&phy->dev);

	rtnl_unlock();
}
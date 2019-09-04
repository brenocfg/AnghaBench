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
struct cfg802154_registered_device {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg802154_rdev_list ; 
 int /*<<< orphan*/  cfg802154_rdev_list_generation ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct cfg802154_registered_device* wpan_phy_to_rdev (struct wpan_phy*) ; 

int wpan_phy_register(struct wpan_phy *phy)
{
	struct cfg802154_registered_device *rdev = wpan_phy_to_rdev(phy);
	int ret;

	rtnl_lock();
	ret = device_add(&phy->dev);
	if (ret) {
		rtnl_unlock();
		return ret;
	}

	list_add_rcu(&rdev->list, &cfg802154_rdev_list);
	cfg802154_rdev_list_generation++;

	/* TODO phy registered lock */
	rtnl_unlock();

	/* TODO nl802154 phy notify */

	return 0;
}
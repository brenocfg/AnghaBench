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
struct ieee802154_local {int /*<<< orphan*/  phy; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  tasklet; } ;
struct ieee802154_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct ieee802154_local* hw_to_local (struct ieee802154_hw*) ; 
 int /*<<< orphan*/  ieee802154_remove_interfaces (struct ieee802154_local*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpan_phy_unregister (int /*<<< orphan*/ ) ; 

void ieee802154_unregister_hw(struct ieee802154_hw *hw)
{
	struct ieee802154_local *local = hw_to_local(hw);

	tasklet_kill(&local->tasklet);
	flush_workqueue(local->workqueue);

	rtnl_lock();

	ieee802154_remove_interfaces(local);

	rtnl_unlock();

	destroy_workqueue(local->workqueue);
	wpan_phy_unregister(local->phy);
}
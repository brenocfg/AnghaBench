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
struct ieee802154_local {int /*<<< orphan*/  phy; int /*<<< orphan*/  iflist_mtx; int /*<<< orphan*/  interfaces; } ;
struct ieee802154_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ieee802154_local* hw_to_local (struct ieee802154_hw*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpan_phy_free (int /*<<< orphan*/ ) ; 

void ieee802154_free_hw(struct ieee802154_hw *hw)
{
	struct ieee802154_local *local = hw_to_local(hw);

	BUG_ON(!list_empty(&local->interfaces));

	mutex_destroy(&local->iflist_mtx);

	wpan_phy_free(local->phy);
}
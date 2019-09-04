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
struct ieee802154_hw {struct fakelb_phy* priv; } ;
struct fakelb_phy {int suspended; int /*<<< orphan*/  list_ifup; } ;

/* Variables and functions */
 int /*<<< orphan*/  fakelb_ifup_phys_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fakelb_hw_stop(struct ieee802154_hw *hw)
{
	struct fakelb_phy *phy = hw->priv;

	write_lock_bh(&fakelb_ifup_phys_lock);
	phy->suspended = true;
	list_del(&phy->list_ifup);
	write_unlock_bh(&fakelb_ifup_phys_lock);
}
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
struct phy_device {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ PHY_HALTED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_disable_interrupts (struct phy_device*) ; 
 scalar_t__ phy_interrupt_is_valid (struct phy_device*) ; 

void phy_stop(struct phy_device *phydev)
{
	mutex_lock(&phydev->lock);

	if (PHY_HALTED == phydev->state)
		goto out_unlock;

	if (phy_interrupt_is_valid(phydev))
		phy_disable_interrupts(phydev);

	phydev->state = PHY_HALTED;

out_unlock:
	mutex_unlock(&phydev->lock);

	/* Cannot call flush_scheduled_work() here as desired because
	 * of rtnl_lock(), but PHY_HALTED shall guarantee phy_change()
	 * will not reenable interrupts.
	 */
}
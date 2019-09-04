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
struct phy_device {int state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  PHY_HALTED 130 
 int PHY_PENDING ; 
#define  PHY_READY 129 
 int PHY_RESUMING ; 
#define  PHY_STARTING 128 
 int PHY_UP ; 
 int /*<<< orphan*/  __phy_resume (struct phy_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_enable_interrupts (struct phy_device*) ; 
 int /*<<< orphan*/  phy_interrupt_is_valid (struct phy_device*) ; 
 int /*<<< orphan*/  phy_trigger_machine (struct phy_device*,int) ; 

void phy_start(struct phy_device *phydev)
{
	int err = 0;

	mutex_lock(&phydev->lock);

	switch (phydev->state) {
	case PHY_STARTING:
		phydev->state = PHY_PENDING;
		break;
	case PHY_READY:
		phydev->state = PHY_UP;
		break;
	case PHY_HALTED:
		/* if phy was suspended, bring the physical link up again */
		__phy_resume(phydev);

		/* make sure interrupts are re-enabled for the PHY */
		if (phy_interrupt_is_valid(phydev)) {
			err = phy_enable_interrupts(phydev);
			if (err < 0)
				break;
		}

		phydev->state = PHY_RESUMING;
		break;
	default:
		break;
	}
	mutex_unlock(&phydev->lock);

	phy_trigger_machine(phydev, true);
}
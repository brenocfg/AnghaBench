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
struct phy_device {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__* drv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* did_interrupt ) (struct phy_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PHY_CHANGELINK ; 
 scalar_t__ PHY_HALTED ; 
 scalar_t__ PHY_NOLINK ; 
 scalar_t__ PHY_RUNNING ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ phy_clear_interrupt (struct phy_device*) ; 
 scalar_t__ phy_disable_interrupts (struct phy_device*) ; 
 int /*<<< orphan*/  phy_error (struct phy_device*) ; 
 scalar_t__ phy_interrupt_is_valid (struct phy_device*) ; 
 int /*<<< orphan*/  phy_trigger_machine (struct phy_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct phy_device*) ; 

__attribute__((used)) static irqreturn_t phy_change(struct phy_device *phydev)
{
	if (phy_interrupt_is_valid(phydev)) {
		if (phydev->drv->did_interrupt &&
		    !phydev->drv->did_interrupt(phydev))
			return IRQ_NONE;

		if (phydev->state == PHY_HALTED)
			if (phy_disable_interrupts(phydev))
				goto phy_err;
	}

	mutex_lock(&phydev->lock);
	if ((PHY_RUNNING == phydev->state) || (PHY_NOLINK == phydev->state))
		phydev->state = PHY_CHANGELINK;
	mutex_unlock(&phydev->lock);

	/* reschedule state queue work to run as soon as possible */
	phy_trigger_machine(phydev, true);

	if (phy_interrupt_is_valid(phydev) && phy_clear_interrupt(phydev))
		goto phy_err;
	return IRQ_HANDLED;

phy_err:
	phy_error(phydev);
	return IRQ_NONE;
}
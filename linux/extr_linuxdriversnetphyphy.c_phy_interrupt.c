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
struct phy_device {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PHY_HALTED ; 
 int /*<<< orphan*/  phy_change (struct phy_device*) ; 

__attribute__((used)) static irqreturn_t phy_interrupt(int irq, void *phy_dat)
{
	struct phy_device *phydev = phy_dat;

	if (PHY_HALTED == phydev->state)
		return IRQ_NONE;		/* It can't be ours.  */

	return phy_change(phydev);
}
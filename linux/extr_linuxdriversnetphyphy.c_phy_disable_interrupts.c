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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_INTERRUPT_DISABLED ; 
 int phy_clear_interrupt (struct phy_device*) ; 
 int phy_config_interrupt (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_disable_interrupts(struct phy_device *phydev)
{
	int err;

	/* Disable PHY interrupts */
	err = phy_config_interrupt(phydev, PHY_INTERRUPT_DISABLED);
	if (err)
		return err;

	/* Clear the interrupt */
	return phy_clear_interrupt(phydev);
}
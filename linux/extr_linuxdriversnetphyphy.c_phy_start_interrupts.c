#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* bus; } ;
struct phy_device {int /*<<< orphan*/  irq; TYPE_2__ mdio; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  PHY_POLL ; 
 int phy_enable_interrupts (struct phy_device*) ; 
 int /*<<< orphan*/  phy_interrupt ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct phy_device*) ; 

int phy_start_interrupts(struct phy_device *phydev)
{
	if (request_threaded_irq(phydev->irq, NULL, phy_interrupt,
				 IRQF_ONESHOT | IRQF_SHARED,
				 phydev_name(phydev), phydev) < 0) {
		pr_warn("%s: Can't get IRQ %d (PHY)\n",
			phydev->mdio.bus->name, phydev->irq);
		phydev->irq = PHY_POLL;
		return 0;
	}

	return phy_enable_interrupts(phydev);
}
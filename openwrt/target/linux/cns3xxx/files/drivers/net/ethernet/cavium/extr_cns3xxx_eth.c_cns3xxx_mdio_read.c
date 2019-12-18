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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int cns3xxx_mdio_cmd (struct mii_bus*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cns3xxx_mdio_read(struct mii_bus *bus, int phy_id, int location)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&mdio_lock, flags);
	ret = cns3xxx_mdio_cmd(bus, phy_id, location, 0, 0);
	spin_unlock_irqrestore(&mdio_lock, flags);
	return ret;
}
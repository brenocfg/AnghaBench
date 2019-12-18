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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {int dummy; } ;
struct b53_device {struct mii_bus* priv; } ;

/* Variables and functions */
 int mdiobus_write (struct mii_bus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b53_mdio_phy_write16(struct b53_device *dev, int addr, u8 reg,
				u16 value)
{
	struct mii_bus *bus = dev->priv;

	return mdiobus_write(bus, addr, reg, value);
}
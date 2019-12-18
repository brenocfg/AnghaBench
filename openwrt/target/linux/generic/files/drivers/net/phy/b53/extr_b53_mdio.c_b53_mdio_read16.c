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
 int /*<<< orphan*/  B53_PSEUDO_PHY ; 
 int /*<<< orphan*/  REG_MII_ADDR_READ ; 
 int /*<<< orphan*/  REG_MII_DATA0 ; 
 int b53_mdio_op (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_read (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b53_mdio_read16(struct b53_device *dev, u8 page, u8 reg, u16 *val)
{
	struct mii_bus *bus = dev->priv;
	int ret;

	ret = b53_mdio_op(dev, page, reg, REG_MII_ADDR_READ);
	if (ret)
		return ret;

	*val = mdiobus_read(bus, B53_PSEUDO_PHY, REG_MII_DATA0);

	return 0;
}
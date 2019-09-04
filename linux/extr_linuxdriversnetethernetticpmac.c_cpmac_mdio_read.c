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
typedef  int u32 ;
struct mii_bus {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_MDIO_ACCESS (int /*<<< orphan*/ ) ; 
 int MDIO_BUSY ; 
 int MDIO_DATA (int) ; 
 int MDIO_PHY (int) ; 
 int MDIO_REG (int) ; 
 int cpmac_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static int cpmac_mdio_read(struct mii_bus *bus, int phy_id, int reg)
{
	u32 val;

	while (cpmac_read(bus->priv, CPMAC_MDIO_ACCESS(0)) & MDIO_BUSY)
		cpu_relax();
	cpmac_write(bus->priv, CPMAC_MDIO_ACCESS(0), MDIO_BUSY | MDIO_REG(reg) |
		    MDIO_PHY(phy_id));
	while ((val = cpmac_read(bus->priv, CPMAC_MDIO_ACCESS(0))) & MDIO_BUSY)
		cpu_relax();

	return MDIO_DATA(val);
}
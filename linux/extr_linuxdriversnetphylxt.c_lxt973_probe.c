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
struct phy_device {int (* priv ) (struct phy_device*) ;} ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_LXT973_PCR ; 
 int PCR_FIBER_SELECT ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lxt973_probe(struct phy_device *phydev)
{
	int val = phy_read(phydev, MII_LXT973_PCR);

	if (val & PCR_FIBER_SELECT) {
		/*
		 * If fiber is selected, then the only correct setting
		 * is 100Mbps, full duplex, and auto negotiation off.
		 */
		val = phy_read(phydev, MII_BMCR);
		val |= (BMCR_SPEED100 | BMCR_FULLDPLX);
		val &= ~BMCR_ANENABLE;
		phy_write(phydev, MII_BMCR, val);
		/* Remember that the port is in fiber mode. */
		phydev->priv = lxt973_probe;
	} else {
		phydev->priv = NULL;
	}
	return 0;
}
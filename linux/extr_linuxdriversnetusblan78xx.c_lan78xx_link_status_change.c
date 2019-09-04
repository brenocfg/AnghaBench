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
struct phy_device {int speed; int /*<<< orphan*/  autoneg; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int /*<<< orphan*/  LAN88XX_INT_MASK ; 
 int LAN88XX_INT_MASK_MDINTPIN_EN_ ; 
 int /*<<< orphan*/  LAN88XX_INT_STS ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan78xx_link_status_change(struct net_device *net)
{
	struct phy_device *phydev = net->phydev;
	int ret, temp;

	/* At forced 100 F/H mode, chip may fail to set mode correctly
	 * when cable is switched between long(~50+m) and short one.
	 * As workaround, set to 10 before setting to 100
	 * at forced 100 F/H mode.
	 */
	if (!phydev->autoneg && (phydev->speed == 100)) {
		/* disable phy interrupt */
		temp = phy_read(phydev, LAN88XX_INT_MASK);
		temp &= ~LAN88XX_INT_MASK_MDINTPIN_EN_;
		ret = phy_write(phydev, LAN88XX_INT_MASK, temp);

		temp = phy_read(phydev, MII_BMCR);
		temp &= ~(BMCR_SPEED100 | BMCR_SPEED1000);
		phy_write(phydev, MII_BMCR, temp); /* set to 10 first */
		temp |= BMCR_SPEED100;
		phy_write(phydev, MII_BMCR, temp); /* set to 100 later */

		/* clear pending interrupt generated while workaround */
		temp = phy_read(phydev, LAN88XX_INT_STS);

		/* enable phy interrupt back */
		temp = phy_read(phydev, LAN88XX_INT_MASK);
		temp |= LAN88XX_INT_MASK_MDINTPIN_EN_;
		ret = phy_write(phydev, LAN88XX_INT_MASK, temp);
	}
}
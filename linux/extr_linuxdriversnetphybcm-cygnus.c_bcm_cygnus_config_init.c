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
 int /*<<< orphan*/  MII_BCM54XX_ECR ; 
 int MII_BCM54XX_ECR_IM ; 
 int /*<<< orphan*/  MII_BCM54XX_IMR ; 
 int MII_BCM54XX_INT_DUPLEX ; 
 int MII_BCM54XX_INT_LINK ; 
 int MII_BCM54XX_INT_SPEED ; 
 int bcm_cygnus_afe_config (struct phy_device*) ; 
 int bcm_phy_enable_apd (struct phy_device*,int) ; 
 int bcm_phy_set_eee (struct phy_device*,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm_cygnus_config_init(struct phy_device *phydev)
{
	int reg, rc;

	reg = phy_read(phydev, MII_BCM54XX_ECR);
	if (reg < 0)
		return reg;

	/* Mask interrupts globally. */
	reg |= MII_BCM54XX_ECR_IM;
	rc = phy_write(phydev, MII_BCM54XX_ECR, reg);
	if (rc)
		return rc;

	/* Unmask events of interest */
	reg = ~(MII_BCM54XX_INT_DUPLEX |
		MII_BCM54XX_INT_SPEED |
		MII_BCM54XX_INT_LINK);
	rc = phy_write(phydev, MII_BCM54XX_IMR, reg);
	if (rc)
		return rc;

	/* Apply AFE settings for the PHY */
	rc = bcm_cygnus_afe_config(phydev);
	if (rc)
		return rc;

	/* Advertise EEE */
	rc = bcm_phy_set_eee(phydev, true);
	if (rc)
		return rc;

	/* Enable APD */
	return bcm_phy_enable_apd(phydev, false);
}
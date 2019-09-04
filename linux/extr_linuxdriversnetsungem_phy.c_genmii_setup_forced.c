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
typedef  int u16 ;
struct mii_phy {int speed; int duplex; scalar_t__ pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_RESET ; 
 int BMCR_SPEED100 ; 
 int DUPLEX_FULL ; 
 int EINVAL ; 
 int /*<<< orphan*/  MII_BMCR ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int sungem_phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sungem_phy_write (struct mii_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int genmii_setup_forced(struct mii_phy *phy, int speed, int fd)
{
	u16 ctl;

	phy->autoneg = 0;
	phy->speed = speed;
	phy->duplex = fd;
	phy->pause = 0;

	ctl = sungem_phy_read(phy, MII_BMCR);
	ctl &= ~(BMCR_FULLDPLX|BMCR_SPEED100|BMCR_ANENABLE);

	/* First reset the PHY */
	sungem_phy_write(phy, MII_BMCR, ctl | BMCR_RESET);

	/* Select speed & duplex */
	switch(speed) {
	case SPEED_10:
		break;
	case SPEED_100:
		ctl |= BMCR_SPEED100;
		break;
	case SPEED_1000:
	default:
		return -EINVAL;
	}
	if (fd == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;
	sungem_phy_write(phy, MII_BMCR, ctl);

	return 0;
}
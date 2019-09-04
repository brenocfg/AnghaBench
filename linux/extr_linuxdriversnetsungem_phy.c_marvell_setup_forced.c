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
 int BMCR_SPD2 ; 
 int BMCR_SPEED100 ; 
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  MII_1000BASETCONTROL ; 
 int MII_1000BASETCONTROL_FULLDUPLEXCAP ; 
 int MII_1000BASETCONTROL_HALFDUPLEXCAP ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_M1011_PHY_SPEC_CONTROL ; 
 int MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX ; 
 int MII_M1011_PHY_SPEC_CONTROL_MANUAL_MDIX ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int sungem_phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sungem_phy_write (struct mii_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int marvell_setup_forced(struct mii_phy *phy, int speed, int fd)
{
	u16 ctl, ctl2;

	phy->autoneg = 0;
	phy->speed = speed;
	phy->duplex = fd;
	phy->pause = 0;

	ctl = sungem_phy_read(phy, MII_BMCR);
	ctl &= ~(BMCR_FULLDPLX|BMCR_SPEED100|BMCR_SPD2|BMCR_ANENABLE);
	ctl |= BMCR_RESET;

	/* Select speed & duplex */
	switch(speed) {
	case SPEED_10:
		break;
	case SPEED_100:
		ctl |= BMCR_SPEED100;
		break;
	/* I'm not sure about the one below, again, Darwin source is
	 * quite confusing and I lack chip specs
	 */
	case SPEED_1000:
		ctl |= BMCR_SPD2;
	}
	if (fd == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;

	/* Disable crossover. Again, the way Apple does it is strange,
	 * though I don't assume they are wrong ;)
	 */
	ctl2 = sungem_phy_read(phy, MII_M1011_PHY_SPEC_CONTROL);
	ctl2 &= ~(MII_M1011_PHY_SPEC_CONTROL_MANUAL_MDIX |
		MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX |
		MII_1000BASETCONTROL_FULLDUPLEXCAP |
		MII_1000BASETCONTROL_HALFDUPLEXCAP);
	if (speed == SPEED_1000)
		ctl2 |= (fd == DUPLEX_FULL) ?
			MII_1000BASETCONTROL_FULLDUPLEXCAP :
			MII_1000BASETCONTROL_HALFDUPLEXCAP;
	sungem_phy_write(phy, MII_1000BASETCONTROL, ctl2);

	// XXX Should we set the sungem to GII now on 1000BT ?

	sungem_phy_write(phy, MII_BMCR, ctl);

	return 0;
}
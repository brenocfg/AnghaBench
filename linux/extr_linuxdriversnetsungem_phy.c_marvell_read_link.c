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
struct mii_phy {int pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int EAGAIN ; 
 int /*<<< orphan*/  MII_M1011_PHY_SPEC_STATUS ; 
 int MII_M1011_PHY_SPEC_STATUS_100 ; 
 int MII_M1011_PHY_SPEC_STATUS_1000 ; 
 int MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX ; 
 int MII_M1011_PHY_SPEC_STATUS_RESOLVED ; 
 int MII_M1011_PHY_SPEC_STATUS_RX_PAUSE ; 
 int MII_M1011_PHY_SPEC_STATUS_TX_PAUSE ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int sungem_phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_read_link(struct mii_phy *phy)
{
	u16 status, pmask;

	if (phy->autoneg) {
		status = sungem_phy_read(phy, MII_M1011_PHY_SPEC_STATUS);
		if ((status & MII_M1011_PHY_SPEC_STATUS_RESOLVED) == 0)
			return -EAGAIN;
		if (status & MII_M1011_PHY_SPEC_STATUS_1000)
			phy->speed = SPEED_1000;
		else if (status & MII_M1011_PHY_SPEC_STATUS_100)
			phy->speed = SPEED_100;
		else
			phy->speed = SPEED_10;
		if (status & MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX)
			phy->duplex = DUPLEX_FULL;
		else
			phy->duplex = DUPLEX_HALF;
		pmask = MII_M1011_PHY_SPEC_STATUS_TX_PAUSE |
			MII_M1011_PHY_SPEC_STATUS_RX_PAUSE;
		phy->pause = (status & pmask) == pmask;
	}
	/* On non-aneg, we assume what we put in BMCR is the speed,
	 * though magic-aneg shouldn't prevent this case from occurring
	 */

	return 0;
}
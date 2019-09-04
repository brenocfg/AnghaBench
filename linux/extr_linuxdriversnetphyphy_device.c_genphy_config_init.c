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
struct phy_device {int supported; int advertising; } ;

/* Variables and functions */
 int BMSR_100FULL ; 
 int BMSR_100HALF ; 
 int BMSR_10FULL ; 
 int BMSR_10HALF ; 
 int BMSR_ANEGCAPABLE ; 
 int BMSR_ESTATEN ; 
 int ESTATUS_1000_TFULL ; 
 int ESTATUS_1000_THALF ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_ESTATUS ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_BNC ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_Pause ; 
 int SUPPORTED_TP ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

int genphy_config_init(struct phy_device *phydev)
{
	int val;
	u32 features;

	features = (SUPPORTED_TP | SUPPORTED_MII
			| SUPPORTED_AUI | SUPPORTED_FIBRE |
			SUPPORTED_BNC | SUPPORTED_Pause | SUPPORTED_Asym_Pause);

	/* Do we support autonegotiation? */
	val = phy_read(phydev, MII_BMSR);
	if (val < 0)
		return val;

	if (val & BMSR_ANEGCAPABLE)
		features |= SUPPORTED_Autoneg;

	if (val & BMSR_100FULL)
		features |= SUPPORTED_100baseT_Full;
	if (val & BMSR_100HALF)
		features |= SUPPORTED_100baseT_Half;
	if (val & BMSR_10FULL)
		features |= SUPPORTED_10baseT_Full;
	if (val & BMSR_10HALF)
		features |= SUPPORTED_10baseT_Half;

	if (val & BMSR_ESTATEN) {
		val = phy_read(phydev, MII_ESTATUS);
		if (val < 0)
			return val;

		if (val & ESTATUS_1000_TFULL)
			features |= SUPPORTED_1000baseT_Full;
		if (val & ESTATUS_1000_THALF)
			features |= SUPPORTED_1000baseT_Half;
	}

	phydev->supported &= features;
	phydev->advertising &= features;

	return 0;
}
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
struct phy_device {int lp_advertising; int advertising; scalar_t__ duplex; int pause; int asym_pause; void* speed; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 scalar_t__ DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 void* SPEED_10000 ; 

void phy_resolve_aneg_linkmode(struct phy_device *phydev)
{
	u32 common = phydev->lp_advertising & phydev->advertising;

	if (common & ADVERTISED_10000baseT_Full) {
		phydev->speed = SPEED_10000;
		phydev->duplex = DUPLEX_FULL;
	} else if (common & ADVERTISED_1000baseT_Full) {
		phydev->speed = SPEED_1000;
		phydev->duplex = DUPLEX_FULL;
	} else if (common & ADVERTISED_1000baseT_Half) {
		phydev->speed = SPEED_1000;
		phydev->duplex = DUPLEX_HALF;
	} else if (common & ADVERTISED_100baseT_Full) {
		phydev->speed = SPEED_100;
		phydev->duplex = DUPLEX_FULL;
	} else if (common & ADVERTISED_100baseT_Half) {
		phydev->speed = SPEED_100;
		phydev->duplex = DUPLEX_HALF;
	} else if (common & ADVERTISED_10baseT_Full) {
		phydev->speed = SPEED_10;
		phydev->duplex = DUPLEX_FULL;
	} else if (common & ADVERTISED_10baseT_Half) {
		phydev->speed = SPEED_10;
		phydev->duplex = DUPLEX_HALF;
	}

	if (phydev->duplex == DUPLEX_FULL) {
		phydev->pause = !!(phydev->lp_advertising & ADVERTISED_Pause);
		phydev->asym_pause = !!(phydev->lp_advertising &
					ADVERTISED_Asym_Pause);
	}
}
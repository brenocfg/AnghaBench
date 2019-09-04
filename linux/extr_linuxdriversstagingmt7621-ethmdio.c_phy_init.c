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
struct phy_device {int supported; int advertising; scalar_t__ duplex; scalar_t__ speed; int /*<<< orphan*/  autoneg; } ;
struct mtk_mac {size_t id; } ;
struct mtk_eth {int /*<<< orphan*/ * netdev; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int PHY_BASIC_FEATURES ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  phy_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 

__attribute__((used)) static void phy_init(struct mtk_eth *eth, struct mtk_mac *mac,
		     struct phy_device *phy)
{
	phy_attach(eth->netdev[mac->id], phydev_name(phy),
		   PHY_INTERFACE_MODE_MII);

	phy->autoneg = AUTONEG_ENABLE;
	phy->speed = 0;
	phy->duplex = 0;
	phy->supported &= PHY_BASIC_FEATURES;
	phy->advertising = phy->supported | ADVERTISED_Autoneg;

	phy_start_aneg(phy);
}
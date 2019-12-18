#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {int supported; int advertising; scalar_t__ duplex; scalar_t__ speed; int /*<<< orphan*/  autoneg; TYPE_1__ mdio; } ;
struct fe_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  CONFIG_NET_MEDIATEK_MDIO_MT7620 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PHY_BASIC_FEATURES ; 
 int PHY_GBIT_FEATURES ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static void phy_init(struct fe_priv *priv, struct phy_device *phy)
{
	phy_attach(priv->netdev, dev_name(&phy->mdio.dev), PHY_INTERFACE_MODE_MII);

	phy->autoneg = AUTONEG_ENABLE;
	phy->speed = 0;
	phy->duplex = 0;
	phy->supported &= IS_ENABLED(CONFIG_NET_MEDIATEK_MDIO_MT7620) ?
			PHY_GBIT_FEATURES : PHY_BASIC_FEATURES;
	phy->advertising = phy->supported | ADVERTISED_Autoneg;

	phy_start_aneg(phy);
}
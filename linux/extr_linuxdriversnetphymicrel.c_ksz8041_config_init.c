#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct phy_device {int supported; int advertising; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  dev_flags; TYPE_2__ mdio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  MICREL_PHY_FXEN ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_FIBRE ; 
 int kszphy_config_init (struct phy_device*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int ksz8041_config_init(struct phy_device *phydev)
{
	struct device_node *of_node = phydev->mdio.dev.of_node;

	/* Limit supported and advertised modes in fiber mode */
	if (of_property_read_bool(of_node, "micrel,fiber-mode")) {
		phydev->dev_flags |= MICREL_PHY_FXEN;
		phydev->supported &= SUPPORTED_100baseT_Full |
				     SUPPORTED_100baseT_Half;
		phydev->supported |= SUPPORTED_FIBRE;
		phydev->advertising &= ADVERTISED_100baseT_Full |
				       ADVERTISED_100baseT_Half;
		phydev->advertising |= ADVERTISED_FIBRE;
		phydev->autoneg = AUTONEG_DISABLE;
	}

	return kszphy_config_init(phydev);
}
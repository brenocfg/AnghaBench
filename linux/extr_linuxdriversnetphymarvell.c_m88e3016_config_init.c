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
 int /*<<< orphan*/  MII_88E3016_AUTO_MDIX_CROSSOVER ; 
 int /*<<< orphan*/  MII_88E3016_DISABLE_SCRAMBLER ; 
 int /*<<< orphan*/  MII_88E3016_PHY_SPEC_CTRL ; 
 int marvell_config_init (struct phy_device*) ; 
 int phy_modify (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88e3016_config_init(struct phy_device *phydev)
{
	int ret;

	/* Enable Scrambler and Auto-Crossover */
	ret = phy_modify(phydev, MII_88E3016_PHY_SPEC_CTRL,
			 MII_88E3016_DISABLE_SCRAMBLER,
			 MII_88E3016_AUTO_MDIX_CROSSOVER);
	if (ret < 0)
		return ret;

	return marvell_config_init(phydev);
}
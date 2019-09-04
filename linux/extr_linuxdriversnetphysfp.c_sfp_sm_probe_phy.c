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
struct sfp {struct phy_device* mod_phy; int /*<<< orphan*/  dev; int /*<<< orphan*/  sfp_bus; int /*<<< orphan*/  i2c_mii; } ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct phy_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SFP_PHY_ADDR ; 
 int /*<<< orphan*/  T_PHY_RESET_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct phy_device* mdiobus_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 int /*<<< orphan*/  phy_device_remove (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int sfp_add_phy (int /*<<< orphan*/ ,struct phy_device*) ; 

__attribute__((used)) static void sfp_sm_probe_phy(struct sfp *sfp)
{
	struct phy_device *phy;
	int err;

	msleep(T_PHY_RESET_MS);

	phy = mdiobus_scan(sfp->i2c_mii, SFP_PHY_ADDR);
	if (phy == ERR_PTR(-ENODEV)) {
		dev_info(sfp->dev, "no PHY detected\n");
		return;
	}
	if (IS_ERR(phy)) {
		dev_err(sfp->dev, "mdiobus scan returned %ld\n", PTR_ERR(phy));
		return;
	}

	err = sfp_add_phy(sfp->sfp_bus, phy);
	if (err) {
		phy_device_remove(phy);
		phy_device_free(phy);
		dev_err(sfp->dev, "sfp_add_phy failed: %d\n", err);
		return;
	}

	sfp->mod_phy = phy;
	phy_start(phy);
}
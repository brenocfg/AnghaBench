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
struct miphy28lp_phy {int /*<<< orphan*/  miphy_rst; struct miphy28lp_dev* phydev; } ;
struct miphy28lp_dev {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_reset_control_get_shared (struct device_node*,char*) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int miphy28lp_probe_resets(struct device_node *node,
				  struct miphy28lp_phy *miphy_phy)
{
	struct miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	int err;

	miphy_phy->miphy_rst =
		of_reset_control_get_shared(node, "miphy-sw-rst");

	if (IS_ERR(miphy_phy->miphy_rst)) {
		dev_err(miphy_dev->dev,
				"miphy soft reset control not defined\n");
		return PTR_ERR(miphy_phy->miphy_rst);
	}

	err = reset_control_deassert(miphy_phy->miphy_rst);
	if (err) {
		dev_err(miphy_dev->dev, "unable to bring out of miphy reset\n");
		return err;
	}

	return 0;
}
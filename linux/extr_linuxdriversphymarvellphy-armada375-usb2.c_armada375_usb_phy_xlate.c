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
struct phy {int dummy; } ;
struct of_phandle_args {scalar_t__* args; } ;
struct device {int dummy; } ;
struct armada375_cluster_phy {scalar_t__ phy_provided; int use_usb3; struct phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ PHY_NONE ; 
 scalar_t__ PHY_TYPE_USB2 ; 
 scalar_t__ PHY_TYPE_USB3 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct armada375_cluster_phy* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *armada375_usb_phy_xlate(struct device *dev,
					struct of_phandle_args *args)
{
	struct armada375_cluster_phy *cluster_phy = dev_get_drvdata(dev);

	if (!cluster_phy)
		return  ERR_PTR(-ENODEV);

	/*
	 * Either the phy had never been requested and then the first
	 * usb claiming it can get it, or it had already been
	 * requested in this case, we only allow to use it with the
	 * same configuration.
	 */
	if (WARN_ON((cluster_phy->phy_provided != PHY_NONE) &&
			(cluster_phy->phy_provided != args->args[0]))) {
		dev_err(dev, "This PHY has already been provided!\n");
		dev_err(dev, "Check your device tree, only one controller can use it\n.");
		if (args->args[0] == PHY_TYPE_USB2)
			return ERR_PTR(-EBUSY);
		else
			return ERR_PTR(-ENODEV);
	}

	if (args->args[0] == PHY_TYPE_USB2)
		cluster_phy->use_usb3 = false;
	else if (args->args[0] == PHY_TYPE_USB3)
		cluster_phy->use_usb3 = true;
	else {
		dev_err(dev, "Invalid PHY mode\n");
		return ERR_PTR(-ENODEV);
	}

	/* Store which phy mode is used for next test */
	cluster_phy->phy_provided = args->args[0];

	return cluster_phy->phy;
}
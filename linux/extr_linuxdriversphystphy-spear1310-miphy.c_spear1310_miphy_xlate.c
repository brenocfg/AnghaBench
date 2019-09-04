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
struct spear1310_miphy_priv {scalar_t__ mode; struct phy* phy; } ;
struct phy {int dummy; } ;
struct of_phandle_args {int args_count; scalar_t__* args; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ PCIE ; 
 scalar_t__ SATA ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct spear1310_miphy_priv* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *spear1310_miphy_xlate(struct device *dev,
					 struct of_phandle_args *args)
{
	struct spear1310_miphy_priv *priv = dev_get_drvdata(dev);

	if (args->args_count < 1) {
		dev_err(dev, "DT did not pass correct no of args\n");
		return ERR_PTR(-ENODEV);
	}

	priv->mode = args->args[0];

	if (priv->mode != SATA && priv->mode != PCIE) {
		dev_err(dev, "DT did not pass correct phy mode\n");
		return ERR_PTR(-ENODEV);
	}

	return priv->phy;
}
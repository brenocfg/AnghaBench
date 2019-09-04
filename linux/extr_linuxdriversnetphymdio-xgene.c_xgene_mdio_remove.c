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
struct xgene_mdio_pdata {int /*<<< orphan*/  clk; struct mii_bus* mdio_bus; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 struct xgene_mdio_pdata* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int xgene_mdio_remove(struct platform_device *pdev)
{
	struct xgene_mdio_pdata *pdata = platform_get_drvdata(pdev);
	struct mii_bus *mdio_bus = pdata->mdio_bus;
	struct device *dev = &pdev->dev;

	mdiobus_unregister(mdio_bus);
	mdiobus_free(mdio_bus);

	if (dev->of_node)
		clk_disable_unprepare(pdata->clk);

	return 0;
}
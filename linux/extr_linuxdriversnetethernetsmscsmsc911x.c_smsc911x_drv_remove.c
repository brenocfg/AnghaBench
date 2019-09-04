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
struct smsc911x_data {int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  mii_bus; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  smsc911x_disable_resources (struct platform_device*) ; 
 int /*<<< orphan*/  smsc911x_free_resources (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int smsc911x_drv_remove(struct platform_device *pdev)
{
	struct net_device *dev;
	struct smsc911x_data *pdata;
	struct resource *res;

	dev = platform_get_drvdata(pdev);
	BUG_ON(!dev);
	pdata = netdev_priv(dev);
	BUG_ON(!pdata);
	BUG_ON(!pdata->ioaddr);

	SMSC_TRACE(pdata, ifdown, "Stopping driver");

	unregister_netdev(dev);

	mdiobus_unregister(pdata->mii_bus);
	mdiobus_free(pdata->mii_bus);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "smsc911x-memory");
	if (!res)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	release_mem_region(res->start, resource_size(res));

	iounmap(pdata->ioaddr);

	(void)smsc911x_disable_resources(pdev);
	smsc911x_free_resources(pdev);

	free_netdev(dev);

	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}
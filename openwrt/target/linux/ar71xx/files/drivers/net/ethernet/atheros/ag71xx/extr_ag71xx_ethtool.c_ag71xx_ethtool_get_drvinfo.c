#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct ag71xx {TYPE_2__* pdev; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_DRV_VERSION ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ag71xx_ethtool_get_drvinfo(struct net_device *dev,
				       struct ethtool_drvinfo *info)
{
	struct ag71xx *ag = netdev_priv(dev);

	strcpy(info->driver, ag->pdev->dev.driver->name);
	strcpy(info->version, AG71XX_DRV_VERSION);
	strcpy(info->bus_info, dev_name(&ag->pdev->dev));
}
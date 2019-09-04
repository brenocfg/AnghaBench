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
struct TYPE_3__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;
struct device {TYPE_2__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ave_hw_read_version (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ave_ethtool_get_drvinfo(struct net_device *ndev,
				    struct ethtool_drvinfo *info)
{
	struct device *dev = ndev->dev.parent;

	strlcpy(info->driver, dev->driver->name, sizeof(info->driver));
	strlcpy(info->bus_info, dev_name(dev), sizeof(info->bus_info));
	ave_hw_read_version(ndev, info->fw_version, sizeof(info->fw_version));
}
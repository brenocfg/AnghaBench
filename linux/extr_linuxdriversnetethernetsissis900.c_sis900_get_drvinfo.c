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
struct sis900_private {int /*<<< orphan*/  pci_dev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIS900_DRV_VERSION ; 
 int /*<<< orphan*/  SIS900_MODULE_NAME ; 
 struct sis900_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sis900_get_drvinfo(struct net_device *net_dev,
			       struct ethtool_drvinfo *info)
{
	struct sis900_private *sis_priv = netdev_priv(net_dev);

	strlcpy(info->driver, SIS900_MODULE_NAME, sizeof(info->driver));
	strlcpy(info->version, SIS900_DRV_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, pci_name(sis_priv->pci_dev),
		sizeof(info->bus_info));
}
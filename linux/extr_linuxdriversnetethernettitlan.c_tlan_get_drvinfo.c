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
struct tlan_priv {scalar_t__ pci_dev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* KBUILD_MODNAME ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 char* pci_name (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void tlan_get_drvinfo(struct net_device *dev,
			     struct ethtool_drvinfo *info)
{
	struct tlan_priv *priv = netdev_priv(dev);

	strlcpy(info->driver, KBUILD_MODNAME, sizeof(info->driver));
	if (priv->pci_dev)
		strlcpy(info->bus_info, pci_name(priv->pci_dev),
			sizeof(info->bus_info));
	else
		strlcpy(info->bus_info, "EISA",	sizeof(info->bus_info));
}
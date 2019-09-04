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
struct ntb_netdev {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  NTB_NETDEV_VER ; 
 struct ntb_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ntb_get_drvinfo(struct net_device *ndev,
			    struct ethtool_drvinfo *info)
{
	struct ntb_netdev *dev = netdev_priv(ndev);

	strlcpy(info->driver, KBUILD_MODNAME, sizeof(info->driver));
	strlcpy(info->version, NTB_NETDEV_VER, sizeof(info->version));
	strlcpy(info->bus_info, pci_name(dev->pdev), sizeof(info->bus_info));
}
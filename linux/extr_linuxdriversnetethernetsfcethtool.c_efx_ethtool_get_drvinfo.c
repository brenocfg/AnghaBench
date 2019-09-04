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
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct efx_nic {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_DRIVER_VERSION ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  efx_mcdi_print_fwver (struct efx_nic*,int /*<<< orphan*/ ,int) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void efx_ethtool_get_drvinfo(struct net_device *net_dev,
				    struct ethtool_drvinfo *info)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	strlcpy(info->driver, KBUILD_MODNAME, sizeof(info->driver));
	strlcpy(info->version, EFX_DRIVER_VERSION, sizeof(info->version));
	efx_mcdi_print_fwver(efx, info->fw_version,
			     sizeof(info->fw_version));
	strlcpy(info->bus_info, pci_name(efx->pci_dev), sizeof(info->bus_info));
}
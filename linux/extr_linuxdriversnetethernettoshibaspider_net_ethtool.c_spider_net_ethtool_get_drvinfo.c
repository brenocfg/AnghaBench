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
struct spider_net_card {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* VERSION ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 char* spider_net_driver_name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
spider_net_ethtool_get_drvinfo(struct net_device *netdev,
			       struct ethtool_drvinfo *drvinfo)
{
	struct spider_net_card *card;
	card = netdev_priv(netdev);

	/* clear and fill out info */
	strlcpy(drvinfo->driver, spider_net_driver_name,
		sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, VERSION, sizeof(drvinfo->version));
	strlcpy(drvinfo->fw_version, "no information",
		sizeof(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(card->pdev),
		sizeof(drvinfo->bus_info));
}
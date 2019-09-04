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
struct ef4_nic {TYPE_2__* net_dev; TYPE_1__* type; int /*<<< orphan*/  phy_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int (* probe_port ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_MODE_SPECIAL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 scalar_t__ phy_flash_cfg ; 
 int /*<<< orphan*/  probe ; 
 int stub1 (struct ef4_nic*) ; 

__attribute__((used)) static int ef4_probe_port(struct ef4_nic *efx)
{
	int rc;

	netif_dbg(efx, probe, efx->net_dev, "create port\n");

	if (phy_flash_cfg)
		efx->phy_mode = PHY_MODE_SPECIAL;

	/* Connect up MAC/PHY operations table */
	rc = efx->type->probe_port(efx);
	if (rc)
		return rc;

	/* Initialise MAC address to permanent address */
	ether_addr_copy(efx->net_dev->dev_addr, efx->net_dev->perm_addr);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ef4_nic {int port_initialized; int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int (* init ) (struct ef4_nic*) ;int (* reconfigure ) (struct ef4_nic*) ;int /*<<< orphan*/  (* fini ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ef4_mac_reconfigure (struct ef4_nic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct ef4_nic*) ; 
 int stub2 (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub3 (struct ef4_nic*) ; 

__attribute__((used)) static int ef4_init_port(struct ef4_nic *efx)
{
	int rc;

	netif_dbg(efx, drv, efx->net_dev, "init port\n");

	mutex_lock(&efx->mac_lock);

	rc = efx->phy_op->init(efx);
	if (rc)
		goto fail1;

	efx->port_initialized = true;

	/* Reconfigure the MAC before creating dma queues (required for
	 * Falcon/A1 where RX_INGR_EN/TX_DRAIN_EN isn't supported) */
	ef4_mac_reconfigure(efx);

	/* Ensure the PHY advertises the correct flow control settings */
	rc = efx->phy_op->reconfigure(efx);
	if (rc && rc != -EPERM)
		goto fail2;

	mutex_unlock(&efx->mac_lock);
	return 0;

fail2:
	efx->phy_op->fini(efx);
fail1:
	mutex_unlock(&efx->mac_lock);
	return rc;
}
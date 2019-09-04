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
struct efx_nic {int port_enabled; int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  efx_mac_reconfigure (struct efx_nic*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void efx_start_port(struct efx_nic *efx)
{
	netif_dbg(efx, ifup, efx->net_dev, "start port\n");
	BUG_ON(efx->port_enabled);

	mutex_lock(&efx->mac_lock);
	efx->port_enabled = true;

	/* Ensure MAC ingress/egress is enabled */
	efx_mac_reconfigure(efx);

	mutex_unlock(&efx->mac_lock);
}
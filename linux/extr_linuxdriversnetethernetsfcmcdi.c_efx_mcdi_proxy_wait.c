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
typedef  scalar_t__ u32 ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_mcdi_iface {scalar_t__ proxy_rx_handle; int proxy_rx_status; int /*<<< orphan*/  proxy_rx_wq; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MCDI_RPC_TIMEOUT ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_mcdi_proxy_wait(struct efx_nic *efx, u32 handle, bool quiet)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	int rc;

	/* Wait for a proxy event, or timeout. */
	rc = wait_event_timeout(mcdi->proxy_rx_wq,
				mcdi->proxy_rx_handle != 0 ||
				mcdi->proxy_rx_status == -EINTR,
				MCDI_RPC_TIMEOUT);

	if (rc <= 0) {
		netif_dbg(efx, hw, efx->net_dev,
			  "MCDI proxy timeout %d\n", handle);
		return -ETIMEDOUT;
	} else if (mcdi->proxy_rx_handle != handle) {
		netif_warn(efx, hw, efx->net_dev,
			   "MCDI proxy unexpected handle %d (expected %d)\n",
			   mcdi->proxy_rx_handle, handle);
		return -EINVAL;
	}

	return mcdi->proxy_rx_status;
}
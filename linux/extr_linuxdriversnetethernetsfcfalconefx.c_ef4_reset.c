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
struct ef4_nic {int reset_pending; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  state; int /*<<< orphan*/  pci_dev; TYPE_1__* type; } ;
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;
struct TYPE_2__ {int (* reset ) (struct ef4_nic*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_TYPE (int) ; 
 int RESET_TYPE_DISABLE ; 
 int RESET_TYPE_MAX_METHOD ; 
 int RESET_TYPE_RECOVER_OR_DISABLE ; 
 int /*<<< orphan*/  STATE_DISABLED ; 
 int /*<<< orphan*/  __clear_bit (int,int*) ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ef4_device_detach_sync (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_reset_down (struct ef4_nic*,int) ; 
 int ef4_reset_up (struct ef4_nic*,int,int) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_info (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int stub1 (struct ef4_nic*,int) ; 

int ef4_reset(struct ef4_nic *efx, enum reset_type method)
{
	int rc, rc2;
	bool disabled;

	netif_info(efx, drv, efx->net_dev, "resetting (%s)\n",
		   RESET_TYPE(method));

	ef4_device_detach_sync(efx);
	ef4_reset_down(efx, method);

	rc = efx->type->reset(efx, method);
	if (rc) {
		netif_err(efx, drv, efx->net_dev, "failed to reset hardware\n");
		goto out;
	}

	/* Clear flags for the scopes we covered.  We assume the NIC and
	 * driver are now quiescent so that there is no race here.
	 */
	if (method < RESET_TYPE_MAX_METHOD)
		efx->reset_pending &= -(1 << (method + 1));
	else /* it doesn't fit into the well-ordered scope hierarchy */
		__clear_bit(method, &efx->reset_pending);

	/* Reinitialise bus-mastering, which may have been turned off before
	 * the reset was scheduled. This is still appropriate, even in the
	 * RESET_TYPE_DISABLE since this driver generally assumes the hardware
	 * can respond to requests. */
	pci_set_master(efx->pci_dev);

out:
	/* Leave device stopped if necessary */
	disabled = rc ||
		method == RESET_TYPE_DISABLE ||
		method == RESET_TYPE_RECOVER_OR_DISABLE;
	rc2 = ef4_reset_up(efx, method, !disabled);
	if (rc2) {
		disabled = true;
		if (!rc)
			rc = rc2;
	}

	if (disabled) {
		dev_close(efx->net_dev);
		netif_err(efx, drv, efx->net_dev, "has been disabled\n");
		efx->state = STATE_DISABLED;
	} else {
		netif_dbg(efx, drv, efx->net_dev, "reset complete\n");
		netif_device_attach(efx->net_dev);
	}
	return rc;
}
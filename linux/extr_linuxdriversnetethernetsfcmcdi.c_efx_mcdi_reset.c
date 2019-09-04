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
struct efx_nic {scalar_t__ mcdi; int /*<<< orphan*/  pci_dev; } ;
struct efx_mcdi_iface {int /*<<< orphan*/  mode; } ;
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;

/* Variables and functions */
 int /*<<< orphan*/  MCDI_MODE_POLL ; 
 int RESET_TYPE_DATAPATH ; 
 int RESET_TYPE_MCDI_TIMEOUT ; 
 int RESET_TYPE_WORLD ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int efx_mcdi_handle_assertion (struct efx_nic*) ; 
 int efx_mcdi_reset_func (struct efx_nic*) ; 
 int efx_mcdi_reset_mc (struct efx_nic*) ; 
 int pci_reset_function (int /*<<< orphan*/ ) ; 

int efx_mcdi_reset(struct efx_nic *efx, enum reset_type method)
{
	int rc;

	/* If MCDI is down, we can't handle_assertion */
	if (method == RESET_TYPE_MCDI_TIMEOUT) {
		rc = pci_reset_function(efx->pci_dev);
		if (rc)
			return rc;
		/* Re-enable polled MCDI completion */
		if (efx->mcdi) {
			struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
			mcdi->mode = MCDI_MODE_POLL;
		}
		return 0;
	}

	/* Recover from a failed assertion pre-reset */
	rc = efx_mcdi_handle_assertion(efx);
	if (rc)
		return rc;

	if (method == RESET_TYPE_DATAPATH)
		return 0;
	else if (method == RESET_TYPE_WORLD)
		return efx_mcdi_reset_mc(efx);
	else
		return efx_mcdi_reset_func(efx);
}
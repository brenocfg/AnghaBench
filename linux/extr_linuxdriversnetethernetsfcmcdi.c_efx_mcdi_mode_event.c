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
struct efx_nic {int /*<<< orphan*/  mcdi; } ;
struct efx_mcdi_iface {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ MCDI_MODE_EVENTS ; 
 scalar_t__ MCDI_MODE_FAIL ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_acquire_sync (struct efx_mcdi_iface*) ; 
 int /*<<< orphan*/  efx_mcdi_release (struct efx_mcdi_iface*) ; 

void efx_mcdi_mode_event(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi;

	if (!efx->mcdi)
		return;

	mcdi = efx_mcdi(efx);
	/* If already in event completion mode, nothing to do.
	 * If in fail-fast state, don't switch to event completion.  FLR
	 * recovery will do that later.
	 */
	if (mcdi->mode == MCDI_MODE_EVENTS || mcdi->mode == MCDI_MODE_FAIL)
		return;

	/* We can't switch from polled to event completion in the middle of a
	 * request, because the completion method is specified in the request.
	 * So acquire the interface to serialise the requestors. We don't need
	 * to acquire the iface_lock to change the mode here, but we do need a
	 * write memory barrier ensure that efx_mcdi_rpc() sees it, which
	 * efx_mcdi_acquire() provides.
	 */
	efx_mcdi_acquire_sync(mcdi);
	mcdi->mode = MCDI_MODE_EVENTS;
	efx_mcdi_release(mcdi);
}
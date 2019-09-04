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
struct efx_nic {TYPE_2__* mcdi; } ;
struct TYPE_3__ {scalar_t__ state; } ;
struct TYPE_4__ {TYPE_1__ iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MCDI_STATE_QUIESCENT ; 
 int /*<<< orphan*/  efx_mcdi_drv_attach (struct efx_nic*,int,int /*<<< orphan*/ *) ; 

void efx_mcdi_detach(struct efx_nic *efx)
{
	if (!efx->mcdi)
		return;

	BUG_ON(efx->mcdi->iface.state != MCDI_STATE_QUIESCENT);

	/* Relinquish the device (back to the BMC, if this is a LOM) */
	efx_mcdi_drv_attach(efx, false, NULL);
}
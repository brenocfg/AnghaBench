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

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void efx_mcdi_fini(struct efx_nic *efx)
{
	if (!efx->mcdi)
		return;

#ifdef CONFIG_SFC_MCDI_LOGGING
	free_page((unsigned long)efx->mcdi->iface.logging_buffer);
#endif

	kfree(efx->mcdi);
}
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
struct efx_nic {scalar_t__ fc_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_mcdi_set_mac (struct efx_nic*) ; 

void siena_finish_flush(struct efx_nic *efx)
{
	if (--efx->fc_disable == 0)
		efx_mcdi_set_mac(efx);
}
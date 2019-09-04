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
typedef  int u32 ;
struct efx_nic {int timer_quantum_ns; int timer_max_ns; TYPE_2__* type; TYPE_1__* net_dev; } ;
struct TYPE_4__ {int timer_period_max; } ;
struct TYPE_3__ {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int MC_CMD_CAPABILITIES_TURBO_ACTIVE_LBN ; 
 int efx_mcdi_get_board_cfg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int siena_probe_nvconfig(struct efx_nic *efx)
{
	u32 caps = 0;
	int rc;

	rc = efx_mcdi_get_board_cfg(efx, efx->net_dev->perm_addr, NULL, &caps);

	efx->timer_quantum_ns =
		(caps & (1 << MC_CMD_CAPABILITIES_TURBO_ACTIVE_LBN)) ?
		3072 : 6144; /* 768 cycles */
	efx->timer_max_ns = efx->type->timer_period_max *
			    efx->timer_quantum_ns;

	return rc;
}
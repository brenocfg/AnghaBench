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
struct efx_nic {TYPE_1__* type; } ;
struct efx_channel {int /*<<< orphan*/  eventq; int /*<<< orphan*/  channel; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;
struct TYPE_2__ {int /*<<< orphan*/  evq_ptr_tbl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_ZERO_OWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FR_BZ_TIMER_TBL ; 
 int /*<<< orphan*/  efx_fini_special_buffer (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void efx_farch_ev_fini(struct efx_channel *channel)
{
	efx_oword_t reg;
	struct efx_nic *efx = channel->efx;

	/* Remove event queue from card */
	EFX_ZERO_OWORD(reg);
	efx_writeo_table(efx, &reg, efx->type->evq_ptr_tbl_base,
			 channel->channel);
	efx_writeo_table(efx, &reg, FR_BZ_TIMER_TBL, channel->channel);

	/* Unpin event queue */
	efx_fini_special_buffer(efx, &channel->eventq);
}
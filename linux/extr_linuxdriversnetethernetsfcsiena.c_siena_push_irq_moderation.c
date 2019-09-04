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
struct efx_nic {int dummy; } ;
struct efx_channel {int /*<<< orphan*/  channel; struct efx_nic* efx; int /*<<< orphan*/  irq_moderation_us; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_DWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FFE_CZ_TIMER_MODE_DIS ; 
 int /*<<< orphan*/  FFE_CZ_TIMER_MODE_INT_HLDOFF ; 
 int /*<<< orphan*/  FRF_CZ_TC_TIMER_MODE ; 
 int /*<<< orphan*/  FRF_CZ_TC_TIMER_VAL ; 
 int /*<<< orphan*/  FR_BZ_TIMER_COMMAND_P0 ; 
 unsigned int efx_usecs_to_ticks (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writed_page_locked (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void siena_push_irq_moderation(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	efx_dword_t timer_cmd;

	if (channel->irq_moderation_us) {
		unsigned int ticks;

		ticks = efx_usecs_to_ticks(efx, channel->irq_moderation_us);
		EFX_POPULATE_DWORD_2(timer_cmd,
				     FRF_CZ_TC_TIMER_MODE,
				     FFE_CZ_TIMER_MODE_INT_HLDOFF,
				     FRF_CZ_TC_TIMER_VAL,
				     ticks - 1);
	} else {
		EFX_POPULATE_DWORD_2(timer_cmd,
				     FRF_CZ_TC_TIMER_MODE,
				     FFE_CZ_TIMER_MODE_DIS,
				     FRF_CZ_TC_TIMER_VAL, 0);
	}
	efx_writed_page_locked(channel->efx, &timer_cmd, FR_BZ_TIMER_COMMAND_P0,
			       channel->channel);
}
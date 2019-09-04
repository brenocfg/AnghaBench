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
struct efx_channel {int eventq_read_ptr; int eventq_mask; int /*<<< orphan*/  channel; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFE_DD_EVQ_IND_RPTR_FLAGS_HIGH ; 
 int /*<<< orphan*/  EFE_DD_EVQ_IND_RPTR_FLAGS_LOW ; 
 scalar_t__ EFX_EF10_WORKAROUND_35388 (struct efx_nic*) ; 
 int EFX_MAX_EVQ_SIZE ; 
 int EFX_MIN_EVQ_SIZE ; 
 int /*<<< orphan*/  EFX_POPULATE_DWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFX_POPULATE_DWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERF_DD_EVQ_IND_RPTR ; 
 int /*<<< orphan*/  ERF_DD_EVQ_IND_RPTR_FLAGS ; 
 int ERF_DD_EVQ_IND_RPTR_WIDTH ; 
 int /*<<< orphan*/  ERF_DZ_EVQ_RPTR ; 
 int /*<<< orphan*/  ER_DD_EVQ_INDIRECT ; 
 int /*<<< orphan*/  ER_DZ_EVQ_RPTR ; 
 int /*<<< orphan*/  efx_writed_page (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_ef10_ev_read_ack(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	efx_dword_t rptr;

	if (EFX_EF10_WORKAROUND_35388(efx)) {
		BUILD_BUG_ON(EFX_MIN_EVQ_SIZE <
			     (1 << ERF_DD_EVQ_IND_RPTR_WIDTH));
		BUILD_BUG_ON(EFX_MAX_EVQ_SIZE >
			     (1 << 2 * ERF_DD_EVQ_IND_RPTR_WIDTH));

		EFX_POPULATE_DWORD_2(rptr, ERF_DD_EVQ_IND_RPTR_FLAGS,
				     EFE_DD_EVQ_IND_RPTR_FLAGS_HIGH,
				     ERF_DD_EVQ_IND_RPTR,
				     (channel->eventq_read_ptr &
				      channel->eventq_mask) >>
				     ERF_DD_EVQ_IND_RPTR_WIDTH);
		efx_writed_page(efx, &rptr, ER_DD_EVQ_INDIRECT,
				channel->channel);
		EFX_POPULATE_DWORD_2(rptr, ERF_DD_EVQ_IND_RPTR_FLAGS,
				     EFE_DD_EVQ_IND_RPTR_FLAGS_LOW,
				     ERF_DD_EVQ_IND_RPTR,
				     channel->eventq_read_ptr &
				     ((1 << ERF_DD_EVQ_IND_RPTR_WIDTH) - 1));
		efx_writed_page(efx, &rptr, ER_DD_EVQ_INDIRECT,
				channel->channel);
	} else {
		EFX_POPULATE_DWORD_1(rptr, ERF_DZ_EVQ_RPTR,
				     channel->eventq_read_ptr &
				     channel->eventq_mask);
		efx_writed_page(efx, &rptr, ER_DZ_EVQ_RPTR, channel->channel);
	}
}
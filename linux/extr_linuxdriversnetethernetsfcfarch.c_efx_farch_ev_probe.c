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
struct efx_channel {int eventq_mask; int /*<<< orphan*/  eventq; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int efx_alloc_special_buffer (struct efx_nic*,int /*<<< orphan*/ *,unsigned int) ; 

int efx_farch_ev_probe(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	unsigned entries;

	entries = channel->eventq_mask + 1;
	return efx_alloc_special_buffer(efx, &channel->eventq,
					entries * sizeof(efx_qword_t));
}
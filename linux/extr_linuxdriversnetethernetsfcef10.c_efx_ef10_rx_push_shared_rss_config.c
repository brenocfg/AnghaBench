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
struct efx_nic {int /*<<< orphan*/  rss_context; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int rx_rss_context_exclusive; } ;

/* Variables and functions */
 int efx_ef10_alloc_rss_context (struct efx_nic*,int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  efx_set_default_rx_indir_table (struct efx_nic*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_rx_push_shared_rss_config(struct efx_nic *efx,
					      unsigned *context_size)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	int rc = efx_ef10_alloc_rss_context(efx, false, &efx->rss_context,
					    context_size);

	if (rc != 0)
		return rc;

	nic_data->rx_rss_context_exclusive = false;
	efx_set_default_rx_indir_table(efx, &efx->rss_context);
	return 0;
}
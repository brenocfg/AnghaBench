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
struct siena_nic_data {struct efx_channel* vfdi_channel; } ;
struct efx_channel {TYPE_1__* efx; } ;
struct TYPE_2__ {struct siena_nic_data* nic_data; } ;

/* Variables and functions */

__attribute__((used)) static int efx_siena_sriov_probe_channel(struct efx_channel *channel)
{
	struct siena_nic_data *nic_data = channel->efx->nic_data;
	nic_data->vfdi_channel = channel;

	return 0;
}
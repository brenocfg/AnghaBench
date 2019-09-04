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
struct siena_vf {int dummy; } ;
struct siena_nic_data {struct siena_vf* vf; } ;
struct efx_nic {unsigned int vf_init_count; struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 unsigned int EFX_VI_BASE ; 
 unsigned int efx_vf_size (struct efx_nic*) ; 

__attribute__((used)) static bool map_vi_index(struct efx_nic *efx, unsigned abs_index,
			 struct siena_vf **vf_out, unsigned *rel_index_out)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	unsigned vf_i;

	if (abs_index < EFX_VI_BASE)
		return true;
	vf_i = (abs_index - EFX_VI_BASE) / efx_vf_size(efx);
	if (vf_i >= efx->vf_init_count)
		return true;

	if (vf_out)
		*vf_out = nic_data->vf + vf_i;
	if (rel_index_out)
		*rel_index_out = abs_index % efx_vf_size(efx);
	return false;
}
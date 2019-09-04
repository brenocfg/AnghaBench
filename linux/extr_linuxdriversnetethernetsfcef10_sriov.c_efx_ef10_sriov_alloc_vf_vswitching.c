#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {unsigned int vf_count; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {TYPE_1__* vf; } ;
struct ef10_vf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan; int /*<<< orphan*/ * efx; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_EF10_NO_VLAN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int efx_ef10_sriov_assign_vf_vport (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_ef10_sriov_free_vf_vports (struct efx_nic*) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 TYPE_1__* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static int efx_ef10_sriov_alloc_vf_vswitching(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	unsigned int i;
	int rc;

	nic_data->vf = kcalloc(efx->vf_count, sizeof(struct ef10_vf),
			       GFP_KERNEL);
	if (!nic_data->vf)
		return -ENOMEM;

	for (i = 0; i < efx->vf_count; i++) {
		eth_random_addr(nic_data->vf[i].mac);
		nic_data->vf[i].efx = NULL;
		nic_data->vf[i].vlan = EFX_EF10_NO_VLAN;

		rc = efx_ef10_sriov_assign_vf_vport(efx, i);
		if (rc)
			goto fail;
	}

	return 0;
fail:
	efx_ef10_sriov_free_vf_vports(efx);
	kfree(nic_data->vf);
	nic_data->vf = NULL;
	return rc;
}
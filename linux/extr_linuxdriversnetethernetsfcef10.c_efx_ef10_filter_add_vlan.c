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
typedef  int /*<<< orphan*/  u16 ;
struct efx_nic {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  filter_sem; struct efx_ef10_filter_table* filter_state; } ;
struct efx_ef10_filter_vlan {int /*<<< orphan*/  list; void** default_filters; void** mc; void** uc; int /*<<< orphan*/  vid; } ;
struct efx_ef10_filter_table {int /*<<< orphan*/  vlan_list; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (void**) ; 
 int EALREADY ; 
 void* EFX_EF10_FILTER_ID_INVALID ; 
 unsigned int EFX_EF10_NUM_DEFAULT_FILTERS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (struct efx_ef10_filter_vlan*) ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ efx_dev_registered (struct efx_nic*) ; 
 struct efx_ef10_filter_vlan* efx_ef10_filter_find_vlan (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ef10_filter_vlan_sync_rx_mode (struct efx_nic*,struct efx_ef10_filter_vlan*) ; 
 int /*<<< orphan*/  efx_rwsem_assert_write_locked (int /*<<< orphan*/ *) ; 
 struct efx_ef10_filter_vlan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ef10_filter_add_vlan(struct efx_nic *efx, u16 vid)
{
	struct efx_ef10_filter_table *table = efx->filter_state;
	struct efx_ef10_filter_vlan *vlan;
	unsigned int i;

	if (!efx_rwsem_assert_write_locked(&efx->filter_sem))
		return -EINVAL;

	vlan = efx_ef10_filter_find_vlan(efx, vid);
	if (WARN_ON(vlan)) {
		netif_err(efx, drv, efx->net_dev,
			  "VLAN %u already added\n", vid);
		return -EALREADY;
	}

	vlan = kzalloc(sizeof(*vlan), GFP_KERNEL);
	if (!vlan)
		return -ENOMEM;

	vlan->vid = vid;

	for (i = 0; i < ARRAY_SIZE(vlan->uc); i++)
		vlan->uc[i] = EFX_EF10_FILTER_ID_INVALID;
	for (i = 0; i < ARRAY_SIZE(vlan->mc); i++)
		vlan->mc[i] = EFX_EF10_FILTER_ID_INVALID;
	for (i = 0; i < EFX_EF10_NUM_DEFAULT_FILTERS; i++)
		vlan->default_filters[i] = EFX_EF10_FILTER_ID_INVALID;

	list_add_tail(&vlan->list, &table->vlan_list);

	if (efx_dev_registered(efx))
		efx_ef10_filter_vlan_sync_rx_mode(efx, vlan);

	return 0;
}
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
struct efx_nic {struct efx_ef10_filter_table* filter_state; } ;
struct efx_ef10_filter_vlan {int /*<<< orphan*/ * default_filters; int /*<<< orphan*/ * mc; int /*<<< orphan*/ * uc; } ;
struct efx_ef10_filter_table {unsigned int dev_uc_count; unsigned int dev_mc_count; } ;

/* Variables and functions */
 unsigned int EFX_EF10_NUM_DEFAULT_FILTERS ; 
 int /*<<< orphan*/  efx_ef10_filter_mark_one_old (struct efx_nic*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _efx_ef10_filter_vlan_mark_old(struct efx_nic *efx,
					   struct efx_ef10_filter_vlan *vlan)
{
	struct efx_ef10_filter_table *table = efx->filter_state;
	unsigned int i;

	for (i = 0; i < table->dev_uc_count; i++)
		efx_ef10_filter_mark_one_old(efx, &vlan->uc[i]);
	for (i = 0; i < table->dev_mc_count; i++)
		efx_ef10_filter_mark_one_old(efx, &vlan->mc[i]);
	for (i = 0; i < EFX_EF10_NUM_DEFAULT_FILTERS; i++)
		efx_ef10_filter_mark_one_old(efx, &vlan->default_filters[i]);
}
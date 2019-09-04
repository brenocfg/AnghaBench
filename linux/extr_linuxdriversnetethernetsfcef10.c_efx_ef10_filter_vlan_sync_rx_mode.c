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
struct efx_nic {struct efx_ef10_nic_data* nic_data; struct efx_ef10_filter_table* filter_state; } ;
struct efx_ef10_nic_data {scalar_t__ workaround_26807; } ;
struct efx_ef10_filter_vlan {scalar_t__ vid; } ;
struct efx_ef10_filter_table {int vlan_filter; scalar_t__ mc_promisc_last; scalar_t__ mc_promisc; int /*<<< orphan*/  mc_overflow; scalar_t__ uc_promisc; } ;

/* Variables and functions */
 int EFX_ENCAP_FLAG_IPV6 ; 
 int EFX_ENCAP_TYPE_GENEVE ; 
 int EFX_ENCAP_TYPE_NONE ; 
 int EFX_ENCAP_TYPE_NVGRE ; 
 int EFX_ENCAP_TYPE_VXLAN ; 
 scalar_t__ EFX_FILTER_VID_UNSPEC ; 
 scalar_t__ efx_ef10_filter_insert_addr_list (struct efx_nic*,struct efx_ef10_filter_vlan*,int,int) ; 
 scalar_t__ efx_ef10_filter_insert_def (struct efx_nic*,struct efx_ef10_filter_vlan*,int,int,int) ; 
 int /*<<< orphan*/  efx_ef10_filter_remove_old (struct efx_nic*) ; 

__attribute__((used)) static void efx_ef10_filter_vlan_sync_rx_mode(struct efx_nic *efx,
					      struct efx_ef10_filter_vlan *vlan)
{
	struct efx_ef10_filter_table *table = efx->filter_state;
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	/* Do not install unspecified VID if VLAN filtering is enabled.
	 * Do not install all specified VIDs if VLAN filtering is disabled.
	 */
	if ((vlan->vid == EFX_FILTER_VID_UNSPEC) == table->vlan_filter)
		return;

	/* Insert/renew unicast filters */
	if (table->uc_promisc) {
		efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NONE,
					   false, false);
		efx_ef10_filter_insert_addr_list(efx, vlan, false, false);
	} else {
		/* If any of the filters failed to insert, fall back to
		 * promiscuous mode - add in the uc_def filter.  But keep
		 * our individual unicast filters.
		 */
		if (efx_ef10_filter_insert_addr_list(efx, vlan, false, false))
			efx_ef10_filter_insert_def(efx, vlan,
						   EFX_ENCAP_TYPE_NONE,
						   false, false);
	}
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_VXLAN,
				   false, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_VXLAN |
					      EFX_ENCAP_FLAG_IPV6,
				   false, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NVGRE,
				   false, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NVGRE |
					      EFX_ENCAP_FLAG_IPV6,
				   false, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_GENEVE,
				   false, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_GENEVE |
					      EFX_ENCAP_FLAG_IPV6,
				   false, false);

	/* Insert/renew multicast filters */
	/* If changing promiscuous state with cascaded multicast filters, remove
	 * old filters first, so that packets are dropped rather than duplicated
	 */
	if (nic_data->workaround_26807 &&
	    table->mc_promisc_last != table->mc_promisc)
		efx_ef10_filter_remove_old(efx);
	if (table->mc_promisc) {
		if (nic_data->workaround_26807) {
			/* If we failed to insert promiscuous filters, rollback
			 * and fall back to individual multicast filters
			 */
			if (efx_ef10_filter_insert_def(efx, vlan,
						       EFX_ENCAP_TYPE_NONE,
						       true, true)) {
				/* Changing promisc state, so remove old filters */
				efx_ef10_filter_remove_old(efx);
				efx_ef10_filter_insert_addr_list(efx, vlan,
								 true, false);
			}
		} else {
			/* If we failed to insert promiscuous filters, don't
			 * rollback.  Regardless, also insert the mc_list,
			 * unless it's incomplete due to overflow
			 */
			efx_ef10_filter_insert_def(efx, vlan,
						   EFX_ENCAP_TYPE_NONE,
						   true, false);
			if (!table->mc_overflow)
				efx_ef10_filter_insert_addr_list(efx, vlan,
								 true, false);
		}
	} else {
		/* If any filters failed to insert, rollback and fall back to
		 * promiscuous mode - mc_def filter and maybe broadcast.  If
		 * that fails, roll back again and insert as many of our
		 * individual multicast filters as we can.
		 */
		if (efx_ef10_filter_insert_addr_list(efx, vlan, true, true)) {
			/* Changing promisc state, so remove old filters */
			if (nic_data->workaround_26807)
				efx_ef10_filter_remove_old(efx);
			if (efx_ef10_filter_insert_def(efx, vlan,
						       EFX_ENCAP_TYPE_NONE,
						       true, true))
				efx_ef10_filter_insert_addr_list(efx, vlan,
								 true, false);
		}
	}
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_VXLAN,
				   true, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_VXLAN |
					      EFX_ENCAP_FLAG_IPV6,
				   true, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NVGRE,
				   true, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NVGRE |
					      EFX_ENCAP_FLAG_IPV6,
				   true, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_GENEVE,
				   true, false);
	efx_ef10_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_GENEVE |
					      EFX_ENCAP_FLAG_IPV6,
				   true, false);
}
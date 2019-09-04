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
struct iwl_mvm {TYPE_1__* fw; int /*<<< orphan*/  hw; } ;
typedef  enum iwl_mvm_traffic_load { ____Placeholder_iwl_mvm_traffic_load } iwl_mvm_traffic_load ;
typedef  enum iwl_mvm_scan_type { ____Placeholder_iwl_mvm_scan_type } iwl_mvm_scan_type ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int IWL_MVM_TRAFFIC_HIGH ; 
 int IWL_MVM_TRAFFIC_MEDIUM ; 
 int IWL_SCAN_TYPE_FRAGMENTED ; 
 int IWL_SCAN_TYPE_MILD ; 
 int IWL_SCAN_TYPE_UNASSOC ; 
 int IWL_SCAN_TYPE_WILD ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_FRAGMENTED_SCAN ; 
 scalar_t__ fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iwl_mvm_scan_condition_iterator ; 

__attribute__((used)) static enum
iwl_mvm_scan_type _iwl_mvm_get_scan_type(struct iwl_mvm *mvm, bool p2p_device,
					 enum iwl_mvm_traffic_load load,
					 bool low_latency)
{
	int global_cnt = 0;

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
					    IEEE80211_IFACE_ITER_NORMAL,
					    iwl_mvm_scan_condition_iterator,
					    &global_cnt);
	if (!global_cnt)
		return IWL_SCAN_TYPE_UNASSOC;

	if ((load == IWL_MVM_TRAFFIC_HIGH || low_latency) && !p2p_device &&
	    fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_FRAGMENTED_SCAN))
		return IWL_SCAN_TYPE_FRAGMENTED;

	if (load >= IWL_MVM_TRAFFIC_MEDIUM || low_latency)
		return IWL_SCAN_TYPE_MILD;

	return IWL_SCAN_TYPE_WILD;
}
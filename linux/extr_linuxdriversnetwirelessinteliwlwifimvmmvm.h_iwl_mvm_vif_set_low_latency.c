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
struct iwl_mvm_vif {int low_latency; } ;
typedef  enum iwl_mvm_low_latency_cause { ____Placeholder_iwl_mvm_low_latency_cause } iwl_mvm_low_latency_cause ;

/* Variables and functions */

__attribute__((used)) static inline
void iwl_mvm_vif_set_low_latency(struct iwl_mvm_vif *mvmvif, bool set,
				 enum iwl_mvm_low_latency_cause cause)
{
	if (set)
		mvmvif->low_latency |= cause;
	else
		mvmvif->low_latency &= ~cause;
}
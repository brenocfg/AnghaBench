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
struct iwl_scan_req_lmac {void* scan_prio; void* suspend_time; void* max_out_time; int /*<<< orphan*/  extended_dwell; int /*<<< orphan*/  fragmented_dwell; int /*<<< orphan*/  passive_dwell; int /*<<< orphan*/  active_dwell; } ;
struct iwl_mvm_scan_params {size_t type; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  suspend_time; int /*<<< orphan*/  max_out_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_SCAN_DWELL_ACTIVE ; 
 int /*<<< orphan*/  IWL_SCAN_DWELL_EXTENDED ; 
 int /*<<< orphan*/  IWL_SCAN_DWELL_FRAGMENTED ; 
 int /*<<< orphan*/  IWL_SCAN_DWELL_PASSIVE ; 
 int /*<<< orphan*/  IWL_SCAN_PRIORITY_EXT_6 ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* scan_timing ; 

__attribute__((used)) static void iwl_mvm_scan_lmac_dwell(struct iwl_mvm *mvm,
				    struct iwl_scan_req_lmac *cmd,
				    struct iwl_mvm_scan_params *params)
{
	cmd->active_dwell = IWL_SCAN_DWELL_ACTIVE;
	cmd->passive_dwell = IWL_SCAN_DWELL_PASSIVE;
	cmd->fragmented_dwell = IWL_SCAN_DWELL_FRAGMENTED;
	cmd->extended_dwell = IWL_SCAN_DWELL_EXTENDED;
	cmd->max_out_time = cpu_to_le32(scan_timing[params->type].max_out_time);
	cmd->suspend_time = cpu_to_le32(scan_timing[params->type].suspend_time);
	cmd->scan_prio = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
}
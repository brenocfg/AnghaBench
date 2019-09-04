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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
struct iwl_beacon_filter_cmd {int /*<<< orphan*/  bf_temp_slow_filter; int /*<<< orphan*/  bf_temp_fast_filter; int /*<<< orphan*/  bf_temp_threshold; int /*<<< orphan*/  bf_roaming_state; int /*<<< orphan*/  bf_roaming_energy_delta; int /*<<< orphan*/  bf_escape_timer; int /*<<< orphan*/  bf_energy_delta; int /*<<< orphan*/  bf_enable_beacon_filter; int /*<<< orphan*/  bf_debug_flag; int /*<<< orphan*/  ba_escape_timer; int /*<<< orphan*/  ba_enable_beacon_abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_POWER (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPLY_BEACON_FILTERING_CMD ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_beacon_filter_cmd*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int iwl_mvm_beacon_filter_send_cmd(struct iwl_mvm *mvm,
				   struct iwl_beacon_filter_cmd *cmd,
				   u32 flags)
{
	IWL_DEBUG_POWER(mvm, "ba_enable_beacon_abort is: %d\n",
			le32_to_cpu(cmd->ba_enable_beacon_abort));
	IWL_DEBUG_POWER(mvm, "ba_escape_timer is: %d\n",
			le32_to_cpu(cmd->ba_escape_timer));
	IWL_DEBUG_POWER(mvm, "bf_debug_flag is: %d\n",
			le32_to_cpu(cmd->bf_debug_flag));
	IWL_DEBUG_POWER(mvm, "bf_enable_beacon_filter is: %d\n",
			le32_to_cpu(cmd->bf_enable_beacon_filter));
	IWL_DEBUG_POWER(mvm, "bf_energy_delta is: %d\n",
			le32_to_cpu(cmd->bf_energy_delta));
	IWL_DEBUG_POWER(mvm, "bf_escape_timer is: %d\n",
			le32_to_cpu(cmd->bf_escape_timer));
	IWL_DEBUG_POWER(mvm, "bf_roaming_energy_delta is: %d\n",
			le32_to_cpu(cmd->bf_roaming_energy_delta));
	IWL_DEBUG_POWER(mvm, "bf_roaming_state is: %d\n",
			le32_to_cpu(cmd->bf_roaming_state));
	IWL_DEBUG_POWER(mvm, "bf_temp_threshold is: %d\n",
			le32_to_cpu(cmd->bf_temp_threshold));
	IWL_DEBUG_POWER(mvm, "bf_temp_fast_filter is: %d\n",
			le32_to_cpu(cmd->bf_temp_fast_filter));
	IWL_DEBUG_POWER(mvm, "bf_temp_slow_filter is: %d\n",
			le32_to_cpu(cmd->bf_temp_slow_filter));

	return iwl_mvm_send_cmd_pdu(mvm, REPLY_BEACON_FILTERING_CMD, flags,
				    sizeof(struct iwl_beacon_filter_cmd), cmd);
}
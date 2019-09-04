#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_tof_config_cmd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_range_request; struct iwl_tof_config_cmd tof_cfg; } ;
struct iwl_mvm {TYPE_1__ tof_data; int /*<<< orphan*/  hw; TYPE_2__* fw; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  IWL_ALWAYS_LONG_GROUP ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_TOF_RANGE_REQ_MAX_ID ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_TOF_SUPPORT ; 
 int /*<<< orphan*/  TOF_CMD ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_tof_config_cmd*) ; 
 int /*<<< orphan*/  iwl_tof_iterator ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_tof_config_cmd(struct iwl_mvm *mvm)
{
	struct iwl_tof_config_cmd *cmd = &mvm->tof_data.tof_cfg;
	bool enabled;

	lockdep_assert_held(&mvm->mutex);

	if (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TOF_SUPPORT))
		return -EINVAL;

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_tof_iterator, &enabled);
	if (!enabled) {
		IWL_DEBUG_INFO(mvm, "ToF is not supported (non bss vif)\n");
		return -EINVAL;
	}

	mvm->tof_data.active_range_request = IWL_MVM_TOF_RANGE_REQ_MAX_ID;
	return iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(TOF_CMD,
						    IWL_ALWAYS_LONG_GROUP, 0),
				    0, sizeof(*cmd), cmd);
}
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
typedef  int /*<<< orphan*/  wowlan_config_cmd ;
typedef  int u32 ;
struct iwl_wowlan_config_cmd {int /*<<< orphan*/  wakeup_filter; int /*<<< orphan*/  wakeup_flags; int /*<<< orphan*/  min_sleep_time; } ;
struct iwl_op_mode {int dummy; } ;
struct TYPE_3__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {scalar_t__ d0i3_ap_sta_id; int d0i3_offloading; TYPE_2__* fw; int /*<<< orphan*/  hw; int /*<<< orphan*/  d0i3_exit_waitq; int /*<<< orphan*/  status; struct iwl_mvm* trans; TYPE_1__ fwrt; } ;
struct iwl_d3_manager_config {int /*<<< orphan*/  wakeup_filter; int /*<<< orphan*/  wakeup_flags; int /*<<< orphan*/  min_sleep_time; } ;
struct iwl_d0i3_iter_data {int vif_count; scalar_t__ ap_sta_id; int /*<<< orphan*/  connected_vif; int /*<<< orphan*/  disable_offloading; struct iwl_mvm* mvm; } ;
typedef  int /*<<< orphan*/  d3_cfg_cmd ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_HIGH_PRIO ; 
 int CMD_MAKE_TRANS_IDLE ; 
 int CMD_SEND_IN_IDLE ; 
 int /*<<< orphan*/  D3_CONFIG_CMD ; 
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_mvm*,char*) ; 
 scalar_t__ IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_D0I3 ; 
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 scalar_t__ IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_BEACON_STORING ; 
 int IWL_WAKEUP_D3_CONFIG_FW_ERROR ; 
 int IWL_WOWLAN_WAKEUP_BCN_FILTERING ; 
 int IWL_WOWLAN_WAKEUP_BEACON_MISS ; 
 int IWL_WOWLAN_WAKEUP_LINK_CHANGE ; 
 int IWL_WOWLAN_WAKEUP_RX_FRAME ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WOWLAN_CONFIGURATION ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_d0i3_iter_data*) ; 
 int /*<<< orphan*/  iwl_mvm_enter_d0i3_iterator ; 
 int iwl_mvm_flush_tx_path (struct iwl_mvm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_mvm_flushable_queues (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_pause_tcm (struct iwl_mvm*,int) ; 
 scalar_t__ iwl_mvm_ref_taken (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int,int,struct iwl_wowlan_config_cmd*) ; 
 int /*<<< orphan*/  iwl_mvm_set_wowlan_data (struct iwl_mvm*,struct iwl_wowlan_config_cmd*,struct iwl_d0i3_iter_data*) ; 
 int /*<<< orphan*/  iwl_mvm_wowlan_config_key_params (struct iwl_mvm*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int iwl_mvm_enter_d0i3(struct iwl_op_mode *op_mode)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	u32 flags = CMD_ASYNC | CMD_HIGH_PRIO | CMD_SEND_IN_IDLE;
	int ret;
	struct iwl_d0i3_iter_data d0i3_iter_data = {
		.mvm = mvm,
	};
	struct iwl_wowlan_config_cmd wowlan_config_cmd = {
		.wakeup_filter = cpu_to_le32(IWL_WOWLAN_WAKEUP_RX_FRAME |
					     IWL_WOWLAN_WAKEUP_BEACON_MISS |
					     IWL_WOWLAN_WAKEUP_LINK_CHANGE),
	};
	struct iwl_d3_manager_config d3_cfg_cmd = {
		.min_sleep_time = cpu_to_le32(1000),
		.wakeup_flags = cpu_to_le32(IWL_WAKEUP_D3_CONFIG_FW_ERROR),
	};

	IWL_DEBUG_RPM(mvm, "MVM entering D0i3\n");

	if (WARN_ON_ONCE(mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR))
		return -EINVAL;

	set_bit(IWL_MVM_STATUS_IN_D0I3, &mvm->status);

	/*
	 * iwl_mvm_ref_sync takes a reference before checking the flag.
	 * so by checking there is no held reference we prevent a state
	 * in which iwl_mvm_ref_sync continues successfully while we
	 * configure the firmware to enter d0i3
	 */
	if (iwl_mvm_ref_taken(mvm)) {
		IWL_DEBUG_RPM(mvm->trans, "abort d0i3 due to taken ref\n");
		clear_bit(IWL_MVM_STATUS_IN_D0I3, &mvm->status);
		wake_up(&mvm->d0i3_exit_waitq);
		return 1;
	}

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_enter_d0i3_iterator,
						   &d0i3_iter_data);
	if (d0i3_iter_data.vif_count == 1) {
		mvm->d0i3_ap_sta_id = d0i3_iter_data.ap_sta_id;
		mvm->d0i3_offloading = !d0i3_iter_data.disable_offloading;
	} else {
		WARN_ON_ONCE(d0i3_iter_data.vif_count > 1);
		mvm->d0i3_ap_sta_id = IWL_MVM_INVALID_STA;
		mvm->d0i3_offloading = false;
	}

	iwl_mvm_pause_tcm(mvm, true);
	/* make sure we have no running tx while configuring the seqno */
	synchronize_net();

	/* Flush the hw queues, in case something got queued during entry */
	/* TODO new tx api */
	if (iwl_mvm_has_new_tx_api(mvm)) {
		WARN_ONCE(1, "d0i3: Need to implement flush TX queue\n");
	} else {
		ret = iwl_mvm_flush_tx_path(mvm, iwl_mvm_flushable_queues(mvm),
					    flags);
		if (ret)
			return ret;
	}

	/* configure wowlan configuration only if needed */
	if (mvm->d0i3_ap_sta_id != IWL_MVM_INVALID_STA) {
		/* wake on beacons only if beacon storing isn't supported */
		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_BEACON_STORING))
			wowlan_config_cmd.wakeup_filter |=
				cpu_to_le32(IWL_WOWLAN_WAKEUP_BCN_FILTERING);

		iwl_mvm_wowlan_config_key_params(mvm,
						 d0i3_iter_data.connected_vif,
						 true, flags);

		iwl_mvm_set_wowlan_data(mvm, &wowlan_config_cmd,
					&d0i3_iter_data);

		ret = iwl_mvm_send_cmd_pdu(mvm, WOWLAN_CONFIGURATION, flags,
					   sizeof(wowlan_config_cmd),
					   &wowlan_config_cmd);
		if (ret)
			return ret;
	}

	return iwl_mvm_send_cmd_pdu(mvm, D3_CONFIG_CMD,
				    flags | CMD_MAKE_TRANS_IDLE,
				    sizeof(d3_cfg_cmd), &d3_cfg_cmd);
}
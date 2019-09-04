#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_2__ ;
typedef  struct error_table_start   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct iwl_wowlan_status {int /*<<< orphan*/  wake_packet_bufsize; } ;
struct iwl_mvm {scalar_t__* error_event_table; int /*<<< orphan*/  trans; } ;
struct iwl_host_cmd {TYPE_2__* resp_pkt; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct ieee80211_vif {int dummy; } ;
struct cfg80211_wowlan_wakeup {int rfkill_release; } ;
typedef  int /*<<< orphan*/  err_info ;
struct TYPE_3__ {scalar_t__ data; } ;
struct error_table_start {scalar_t__ valid; scalar_t__ error_id; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int EIO ; 
 struct iwl_wowlan_status* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_mvm*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  OFFLOADS_QUERY_CMD ; 
 scalar_t__ RF_KILL_INDICATOR_FOR_WOWLAN ; 
 int /*<<< orphan*/  WOWLAN_GET_STATUSES ; 
 int /*<<< orphan*/  ieee80211_report_wowlan_wakeup (struct ieee80211_vif*,struct cfg80211_wowlan_wakeup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iwl_rx_packet_payload_len (TYPE_2__*) ; 
 int /*<<< orphan*/  iwl_trans_read_mem_bytes (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int) ; 
 struct iwl_wowlan_status* kmemdup (struct iwl_wowlan_status*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iwl_wowlan_status *
iwl_mvm_get_wakeup_status(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	u32 base = mvm->error_event_table[0];
	struct error_table_start {
		/* cf. struct iwl_error_event_table */
		u32 valid;
		u32 error_id;
	} err_info;
	struct iwl_host_cmd cmd = {
		.id = WOWLAN_GET_STATUSES,
		.flags = CMD_WANT_SKB,
	};
	struct iwl_wowlan_status *status, *fw_status;
	int ret, len, status_size;

	iwl_trans_read_mem_bytes(mvm->trans, base,
				 &err_info, sizeof(err_info));

	if (err_info.valid) {
		IWL_INFO(mvm, "error table is valid (%d) with error (%d)\n",
			 err_info.valid, err_info.error_id);
		if (err_info.error_id == RF_KILL_INDICATOR_FOR_WOWLAN) {
			struct cfg80211_wowlan_wakeup wakeup = {
				.rfkill_release = true,
			};
			ieee80211_report_wowlan_wakeup(vif, &wakeup,
						       GFP_KERNEL);
		}
		return ERR_PTR(-EIO);
	}

	/* only for tracing for now */
	ret = iwl_mvm_send_cmd_pdu(mvm, OFFLOADS_QUERY_CMD, 0, 0, NULL);
	if (ret)
		IWL_ERR(mvm, "failed to query offload statistics (%d)\n", ret);

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	if (ret) {
		IWL_ERR(mvm, "failed to query status (%d)\n", ret);
		return ERR_PTR(ret);
	}

	status_size = sizeof(*fw_status);

	len = iwl_rx_packet_payload_len(cmd.resp_pkt);
	if (len < status_size) {
		IWL_ERR(mvm, "Invalid WoWLAN status response!\n");
		fw_status = ERR_PTR(-EIO);
		goto out_free_resp;
	}

	status = (void *)cmd.resp_pkt->data;
	if (len != (status_size +
		    ALIGN(le32_to_cpu(status->wake_packet_bufsize), 4))) {
		IWL_ERR(mvm, "Invalid WoWLAN status response!\n");
		fw_status = ERR_PTR(-EIO);
		goto out_free_resp;
	}

	fw_status = kmemdup(status, len, GFP_KERNEL);

out_free_resp:
	iwl_free_resp(&cmd);
	return fw_status;
}
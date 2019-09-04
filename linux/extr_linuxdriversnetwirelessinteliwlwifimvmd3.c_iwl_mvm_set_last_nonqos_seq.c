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
struct iwl_nonqos_seq_query_cmd {int /*<<< orphan*/  value; int /*<<< orphan*/  mac_id_n_color; int /*<<< orphan*/  get_set_flag; } ;
struct iwl_mvm_vif {int seqno_valid; int /*<<< orphan*/  seqno; int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
typedef  int /*<<< orphan*/  query_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_NONQOS_SEQ_SET ; 
 int /*<<< orphan*/  NON_QOS_TX_COUNTER_CMD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_nonqos_seq_query_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

void iwl_mvm_set_last_nonqos_seq(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_nonqos_seq_query_cmd query_cmd = {
		.get_set_flag = cpu_to_le32(IWL_NONQOS_SEQ_SET),
		.mac_id_n_color =
			cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->id,
							mvmvif->color)),
		.value = cpu_to_le16(mvmvif->seqno),
	};

	/* return if called during restart, not resume from D3 */
	if (!mvmvif->seqno_valid)
		return;

	mvmvif->seqno_valid = false;

	if (iwl_mvm_send_cmd_pdu(mvm, NON_QOS_TX_COUNTER_CMD, 0,
				 sizeof(query_cmd), &query_cmd))
		IWL_ERR(mvm, "failed to set non-QoS seqno\n");
}
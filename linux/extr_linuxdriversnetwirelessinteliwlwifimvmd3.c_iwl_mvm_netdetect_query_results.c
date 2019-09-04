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
struct iwl_scan_offload_profiles_query {int /*<<< orphan*/  matches; int /*<<< orphan*/  matched_profiles; } ;
struct iwl_mvm_nd_query_results {int /*<<< orphan*/  matches; int /*<<< orphan*/  matched_profiles; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_host_cmd {TYPE_1__* resp_pkt; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  SCAN_OFFLOAD_PROFILES_QUERY_CMD ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 
 int iwl_rx_packet_payload_len (TYPE_1__*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwl_mvm_netdetect_query_results(struct iwl_mvm *mvm,
				struct iwl_mvm_nd_query_results *results)
{
	struct iwl_scan_offload_profiles_query *query;
	struct iwl_host_cmd cmd = {
		.id = SCAN_OFFLOAD_PROFILES_QUERY_CMD,
		.flags = CMD_WANT_SKB,
	};
	int ret, len;

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	if (ret) {
		IWL_ERR(mvm, "failed to query matched profiles (%d)\n", ret);
		return ret;
	}

	len = iwl_rx_packet_payload_len(cmd.resp_pkt);
	if (len < sizeof(*query)) {
		IWL_ERR(mvm, "Invalid scan offload profiles query response!\n");
		ret = -EIO;
		goto out_free_resp;
	}

	query = (void *)cmd.resp_pkt->data;

	results->matched_profiles = le32_to_cpu(query->matched_profiles);
	memcpy(results->matches, query->matches, sizeof(results->matches));

#ifdef CONFIG_IWLWIFI_DEBUGFS
	mvm->last_netdetect_scans = le32_to_cpu(query->n_scans_done);
#endif

out_free_resp:
	iwl_free_resp(&cmd);
	return ret;
}
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
struct iwl_tof_gen_resp_cmd {int /*<<< orphan*/  sub_grp_cmd_id; int /*<<< orphan*/  data; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
#define  TOF_MCSI_DEBUG_NOTIF 130 
#define  TOF_NEIGHBOR_REPORT_RSP_NOTIF 129 
#define  TOF_RANGE_RESPONSE_NOTIF 128 
 int /*<<< orphan*/  iwl_mvm_tof_mcsi_notif (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_tof_nb_report_notif (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_tof_range_resp (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_tof_resp_handler(struct iwl_mvm *mvm,
			      struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_tof_gen_resp_cmd *resp = (void *)pkt->data;

	lockdep_assert_held(&mvm->mutex);

	switch (le32_to_cpu(resp->sub_grp_cmd_id)) {
	case TOF_RANGE_RESPONSE_NOTIF:
		iwl_mvm_tof_range_resp(mvm, resp->data);
		break;
	case TOF_MCSI_DEBUG_NOTIF:
		iwl_mvm_tof_mcsi_notif(mvm, resp->data);
		break;
	case TOF_NEIGHBOR_REPORT_RSP_NOTIF:
		iwl_mvm_tof_nb_report_notif(mvm, resp->data);
		break;
	default:
	       IWL_ERR(mvm, "Unknown sub-group command 0x%x\n",
		       resp->sub_grp_cmd_id);
	       break;
	}
}
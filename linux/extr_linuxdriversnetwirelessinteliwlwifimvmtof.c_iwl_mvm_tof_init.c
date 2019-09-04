#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* sub_grp_cmd_id; } ;
struct TYPE_7__ {int req_timeout; int initiator; int report_policy; void* sub_grp_cmd_id; } ;
struct TYPE_6__ {void* sub_grp_cmd_id; } ;
struct iwl_mvm_tof_data {int /*<<< orphan*/  active_range_request; TYPE_4__ range_req_ext; TYPE_3__ range_req; TYPE_2__ tof_cfg; } ;
struct iwl_mvm {int /*<<< orphan*/  init_status; struct iwl_mvm_tof_data tof_data; TYPE_1__* fw; } ;
struct TYPE_5__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_INIT_STATUS_TOF_INIT_COMPLETE ; 
 int /*<<< orphan*/  IWL_MVM_TOF_RANGE_REQ_MAX_ID ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_TOF_SUPPORT ; 
 int /*<<< orphan*/  TOF_CONFIG_CMD ; 
 int /*<<< orphan*/  TOF_RANGE_REQ_CMD ; 
 int /*<<< orphan*/  TOF_RANGE_REQ_EXT_CMD ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_mvm_tof_data*,int /*<<< orphan*/ ,int) ; 

void iwl_mvm_tof_init(struct iwl_mvm *mvm)
{
	struct iwl_mvm_tof_data *tof_data = &mvm->tof_data;

	if (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TOF_SUPPORT))
		return;

	memset(tof_data, 0, sizeof(*tof_data));

	tof_data->tof_cfg.sub_grp_cmd_id = cpu_to_le32(TOF_CONFIG_CMD);

#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (IWL_MVM_TOF_IS_RESPONDER) {
		tof_data->responder_cfg.sub_grp_cmd_id =
			cpu_to_le32(TOF_RESPONDER_CONFIG_CMD);
		tof_data->responder_cfg.sta_id = IWL_MVM_INVALID_STA;
	}
#endif

	tof_data->range_req.sub_grp_cmd_id = cpu_to_le32(TOF_RANGE_REQ_CMD);
	tof_data->range_req.req_timeout = 1;
	tof_data->range_req.initiator = 1;
	tof_data->range_req.report_policy = 3;

	tof_data->range_req_ext.sub_grp_cmd_id =
		cpu_to_le32(TOF_RANGE_REQ_EXT_CMD);

	mvm->tof_data.active_range_request = IWL_MVM_TOF_RANGE_REQ_MAX_ID;
	mvm->init_status |= IWL_MVM_INIT_STATUS_TOF_INIT_COMPLETE;
}
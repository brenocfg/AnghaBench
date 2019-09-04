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
typedef  scalar_t__ u8 ;
struct iwl_tof_range_abort_cmd {scalar_t__ request_id; int /*<<< orphan*/  sub_grp_cmd_id; } ;
struct TYPE_4__ {scalar_t__ active_range_request; } ;
struct iwl_mvm {TYPE_2__ tof_data; TYPE_1__* fw; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_ALWAYS_LONG_GROUP ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ IWL_MVM_TOF_RANGE_REQ_MAX_ID ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_TOF_SUPPORT ; 
 int /*<<< orphan*/  TOF_CMD ; 
 int /*<<< orphan*/  TOF_RANGE_ABORT_CMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_tof_range_abort_cmd*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_tof_range_abort_cmd(struct iwl_mvm *mvm, u8 id)
{
	struct iwl_tof_range_abort_cmd cmd = {
		.sub_grp_cmd_id = cpu_to_le32(TOF_RANGE_ABORT_CMD),
		.request_id = id,
	};

	lockdep_assert_held(&mvm->mutex);

	if (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TOF_SUPPORT))
		return -EINVAL;

	if (id != mvm->tof_data.active_range_request) {
		IWL_ERR(mvm, "Invalid range request id %d (active %d)\n",
			id, mvm->tof_data.active_range_request);
		return -EINVAL;
	}

	/* after abort is sent there's no active request anymore */
	mvm->tof_data.active_range_request = IWL_MVM_TOF_RANGE_REQ_MAX_ID;

	return iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(TOF_CMD,
						    IWL_ALWAYS_LONG_GROUP, 0),
				    0, sizeof(cmd), &cmd);
}
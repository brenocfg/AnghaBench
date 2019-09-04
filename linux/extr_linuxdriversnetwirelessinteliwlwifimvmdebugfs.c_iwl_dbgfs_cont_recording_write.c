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
struct iwl_trans {TYPE_1__* cfg; struct iwl_fw_dbg_dest_tlv_v1* dbg_dest_tlv; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; struct iwl_trans* trans; } ;
struct iwl_fw_dbg_dest_tlv_v1 {scalar_t__ monitor_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable_recording; } ;
struct iwl_continuous_record_cmd {TYPE_2__ record_mode; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  cont_rec ;
struct TYPE_3__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_CONT_RECORDING ; 
 int EIO ; 
 int /*<<< orphan*/  ENABLE_CONT_RECORDING ; 
 int EOPNOTSUPP ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  LDBG_CONFIG_CMD ; 
 scalar_t__ SMEM_MODE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_continuous_record_cmd*) ; 
 int kstrtoint (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_cont_recording_write(struct iwl_mvm *mvm,
					      char *buf, size_t count,
					      loff_t *ppos)
{
	struct iwl_trans *trans = mvm->trans;
	const struct iwl_fw_dbg_dest_tlv_v1 *dest = trans->dbg_dest_tlv;
	struct iwl_continuous_record_cmd cont_rec = {};
	int ret, rec_mode;

	if (!iwl_mvm_firmware_running(mvm))
		return -EIO;

	if (!dest)
		return -EOPNOTSUPP;

	if (dest->monitor_mode != SMEM_MODE ||
	    trans->cfg->device_family < IWL_DEVICE_FAMILY_8000)
		return -EOPNOTSUPP;

	ret = kstrtoint(buf, 0, &rec_mode);
	if (ret)
		return ret;

	cont_rec.record_mode.enable_recording = rec_mode ?
		cpu_to_le16(ENABLE_CONT_RECORDING) :
		cpu_to_le16(DISABLE_CONT_RECORDING);

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd_pdu(mvm, LDBG_CONFIG_CMD, 0,
				   sizeof(cont_rec), &cont_rec);
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}
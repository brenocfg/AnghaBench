#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct iwl_trans {TYPE_1__* cfg; } ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm_alive_data {int /*<<< orphan*/  scd_base_addr; int /*<<< orphan*/  valid; } ;
struct TYPE_9__ {int cur_fw_img; } ;
struct iwl_mvm {int /*<<< orphan*/  status; int /*<<< orphan*/ * mac80211_queue_stop_count; TYPE_2__* queue_info; struct iwl_trans* trans; TYPE_4__ fwrt; int /*<<< orphan*/  notif_wait; TYPE_3__* fw; } ;
struct fw_img {int dummy; } ;
typedef  enum iwl_ucode_type { ____Placeholder_iwl_ucode_type } iwl_ucode_type ;
struct TYPE_8__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_7__ {int hw_queue_refcount; } ;
struct TYPE_6__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FW_DBG_START_FROM_ALIVE ; 
 int IEEE80211_MAX_QUEUES ; 
 scalar_t__ IWL_DEVICE_FAMILY_22000 ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 size_t IWL_MVM_DQA_CMD_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_FIRMWARE_RUNNING ; 
 int IWL_UCODE_INIT ; 
 int IWL_UCODE_REGULAR ; 
 int IWL_UCODE_REGULAR_USNIFFER ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_USNIFFER_UNIFIED ; 
#define  MVM_ALIVE 128 
 int /*<<< orphan*/  MVM_UCODE_ALIVE_TIMEOUT ; 
 int /*<<< orphan*/  SB_CPU_1_STATUS ; 
 int /*<<< orphan*/  SB_CPU_2_STATUS ; 
 int /*<<< orphan*/  UMAG_SB_CPU_1_STATUS ; 
 int /*<<< orphan*/  UMAG_SB_CPU_2_STATUS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_alive_fn ; 
 scalar_t__ iwl_fw_dbg_conf_usniffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_set_current_image (TYPE_4__*,int) ; 
 struct fw_img* iwl_get_ucode_image (TYPE_3__*,int) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_alive_data*) ; 
 int /*<<< orphan*/  iwl_read_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int /*<<< orphan*/  iwl_trans_fw_alive (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_trans_start_fw (struct iwl_trans*,struct fw_img const*,int) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_load_ucode_wait_alive(struct iwl_mvm *mvm,
					 enum iwl_ucode_type ucode_type)
{
	struct iwl_notification_wait alive_wait;
	struct iwl_mvm_alive_data alive_data;
	const struct fw_img *fw;
	int ret, i;
	enum iwl_ucode_type old_type = mvm->fwrt.cur_fw_img;
	static const u16 alive_cmd[] = { MVM_ALIVE };

	if (ucode_type == IWL_UCODE_REGULAR &&
	    iwl_fw_dbg_conf_usniffer(mvm->fw, FW_DBG_START_FROM_ALIVE) &&
	    !(fw_has_capa(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_CAPA_USNIFFER_UNIFIED)))
		fw = iwl_get_ucode_image(mvm->fw, IWL_UCODE_REGULAR_USNIFFER);
	else
		fw = iwl_get_ucode_image(mvm->fw, ucode_type);
	if (WARN_ON(!fw))
		return -EINVAL;
	iwl_fw_set_current_image(&mvm->fwrt, ucode_type);
	clear_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);

	iwl_init_notification_wait(&mvm->notif_wait, &alive_wait,
				   alive_cmd, ARRAY_SIZE(alive_cmd),
				   iwl_alive_fn, &alive_data);

	ret = iwl_trans_start_fw(mvm->trans, fw, ucode_type == IWL_UCODE_INIT);
	if (ret) {
		iwl_fw_set_current_image(&mvm->fwrt, old_type);
		iwl_remove_notification(&mvm->notif_wait, &alive_wait);
		return ret;
	}

	/*
	 * Some things may run in the background now, but we
	 * just wait for the ALIVE notification here.
	 */
	ret = iwl_wait_notification(&mvm->notif_wait, &alive_wait,
				    MVM_UCODE_ALIVE_TIMEOUT);
	if (ret) {
		struct iwl_trans *trans = mvm->trans;

		if (trans->cfg->device_family >= IWL_DEVICE_FAMILY_22000)
			IWL_ERR(mvm,
				"SecBoot CPU1 Status: 0x%x, CPU2 Status: 0x%x\n",
				iwl_read_prph(trans, UMAG_SB_CPU_1_STATUS),
				iwl_read_prph(trans, UMAG_SB_CPU_2_STATUS));
		else if (trans->cfg->device_family >= IWL_DEVICE_FAMILY_8000)
			IWL_ERR(mvm,
				"SecBoot CPU1 Status: 0x%x, CPU2 Status: 0x%x\n",
				iwl_read_prph(trans, SB_CPU_1_STATUS),
				iwl_read_prph(trans, SB_CPU_2_STATUS));
		iwl_fw_set_current_image(&mvm->fwrt, old_type);
		return ret;
	}

	if (!alive_data.valid) {
		IWL_ERR(mvm, "Loaded ucode is not valid!\n");
		iwl_fw_set_current_image(&mvm->fwrt, old_type);
		return -EIO;
	}

	iwl_trans_fw_alive(mvm->trans, alive_data.scd_base_addr);

	/*
	 * Note: all the queues are enabled as part of the interface
	 * initialization, but in firmware restart scenarios they
	 * could be stopped, so wake them up. In firmware restart,
	 * mac80211 will have the queues stopped as well until the
	 * reconfiguration completes. During normal startup, they
	 * will be empty.
	 */

	memset(&mvm->queue_info, 0, sizeof(mvm->queue_info));
	mvm->queue_info[IWL_MVM_DQA_CMD_QUEUE].hw_queue_refcount = 1;

	for (i = 0; i < IEEE80211_MAX_QUEUES; i++)
		atomic_set(&mvm->mac80211_queue_stop_count[i], 0);

	set_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);

	return 0;
}
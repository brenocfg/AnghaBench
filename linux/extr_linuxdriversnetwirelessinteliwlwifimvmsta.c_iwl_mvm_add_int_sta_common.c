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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm_int_sta {int /*<<< orphan*/  tfd_queue_msk; int /*<<< orphan*/  type; int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm_add_sta_cmd {int /*<<< orphan*/  addr; int /*<<< orphan*/  tid_disable_tx; void* tfd_queue_msk; int /*<<< orphan*/  station_type; void* mac_id_n_color; int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {TYPE_1__* fw; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STA ; 
#define  ADD_STA_SUCCESS 128 
 int EIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IWL_ADD_STA_STATUS_MASK ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_STA_TYPE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_add_sta_cmd_size (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu_status (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_add_sta_cmd*,int*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_mvm_add_sta_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_mvm_add_int_sta_common(struct iwl_mvm *mvm,
				      struct iwl_mvm_int_sta *sta,
				      const u8 *addr,
				      u16 mac_id, u16 color)
{
	struct iwl_mvm_add_sta_cmd cmd;
	int ret;
	u32 status = ADD_STA_SUCCESS;

	lockdep_assert_held(&mvm->mutex);

	memset(&cmd, 0, sizeof(cmd));
	cmd.sta_id = sta->sta_id;
	cmd.mac_id_n_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(mac_id,
							     color));
	if (fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE))
		cmd.station_type = sta->type;

	if (!iwl_mvm_has_new_tx_api(mvm))
		cmd.tfd_queue_msk = cpu_to_le32(sta->tfd_queue_msk);
	cmd.tid_disable_tx = cpu_to_le16(0xffff);

	if (addr)
		memcpy(cmd.addr, addr, ETH_ALEN);

	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA,
					  iwl_mvm_add_sta_cmd_size(mvm),
					  &cmd, &status);
	if (ret)
		return ret;

	switch (status & IWL_ADD_STA_STATUS_MASK) {
	case ADD_STA_SUCCESS:
		IWL_DEBUG_INFO(mvm, "Internal station added.\n");
		return 0;
	default:
		ret = -EIO;
		IWL_ERR(mvm, "Add internal station failed, status=0x%x\n",
			status);
		break;
	}
	return ret;
}
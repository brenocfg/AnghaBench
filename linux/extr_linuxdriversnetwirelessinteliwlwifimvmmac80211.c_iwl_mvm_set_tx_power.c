#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm {TYPE_1__* fw; } ;
struct TYPE_5__ {int /*<<< orphan*/  pwr_restriction; int /*<<< orphan*/  mac_context_id; int /*<<< orphan*/  set_mode; } ;
struct iwl_dev_tx_power_cmd {TYPE_2__ v3; } ;
struct ieee80211_vif {int dummy; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int IWL_DEFAULT_MAX_TX_POWER ; 
 int IWL_DEV_MAX_TX_POWER ; 
 int /*<<< orphan*/  IWL_TX_POWER_MODE_SET_MAC ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_TX_POWER_ACK ; 
 int /*<<< orphan*/  REDUCE_TX_POWER_CMD ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_dev_tx_power_cmd*) ; 
 TYPE_3__* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static int iwl_mvm_set_tx_power(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
				s16 tx_power)
{
	struct iwl_dev_tx_power_cmd cmd = {
		.v3.set_mode = cpu_to_le32(IWL_TX_POWER_MODE_SET_MAC),
		.v3.mac_context_id =
			cpu_to_le32(iwl_mvm_vif_from_mac80211(vif)->id),
		.v3.pwr_restriction = cpu_to_le16(8 * tx_power),
	};
	int len = sizeof(cmd);

	if (tx_power == IWL_DEFAULT_MAX_TX_POWER)
		cmd.v3.pwr_restriction = cpu_to_le16(IWL_DEV_MAX_TX_POWER);

	if (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TX_POWER_ACK))
		len = sizeof(cmd.v3);

	return iwl_mvm_send_cmd_pdu(mvm, REDUCE_TX_POWER_CMD, 0, len, &cmd);
}
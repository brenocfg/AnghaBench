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
struct TYPE_4__ {int /*<<< orphan*/  range_req_ext; } ;
struct iwl_mvm {TYPE_2__ tof_data; TYPE_1__* fw; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_ALWAYS_LONG_GROUP ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_TOF_SUPPORT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  TOF_CMD ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_vif_type_p2p (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_tof_range_request_ext_cmd(struct iwl_mvm *mvm,
				      struct ieee80211_vif *vif)
{
	lockdep_assert_held(&mvm->mutex);

	if (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TOF_SUPPORT))
		return -EINVAL;

	if (ieee80211_vif_type_p2p(vif) !=  NL80211_IFTYPE_STATION) {
		IWL_ERR(mvm, "Cannot send ext range req, not in STA mode\n");
		return -EIO;
	}

	return iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(TOF_CMD,
						    IWL_ALWAYS_LONG_GROUP, 0),
				    0, sizeof(mvm->tof_data.range_req_ext),
				    &mvm->tof_data.range_req_ext);
}
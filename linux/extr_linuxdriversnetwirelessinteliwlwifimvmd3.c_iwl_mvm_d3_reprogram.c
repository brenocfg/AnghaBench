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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_time_quota_data {void* id_and_color; void* max_duration; void* quota; } ;
struct iwl_time_quota_cmd {int dummy; } ;
struct iwl_mvm_vif {int uploaded; size_t ap_sta_id; TYPE_4__* phy_ctxt; int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; TYPE_1__* fw; } ;
struct iwl_binding_cmd {void** macs; void* phy; void* action; void* id_and_color; void* lmac_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {TYPE_3__ bss_conf; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sta {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;
struct ieee80211_chanctx_conf {int /*<<< orphan*/  rx_chains_dynamic; int /*<<< orphan*/  rx_chains_static; struct cfg80211_chan_def def; } ;
typedef  int /*<<< orphan*/  binding_cmd ;
struct TYPE_8__ {int /*<<< orphan*/  color; int /*<<< orphan*/  id; TYPE_2__* channel; } ;
struct TYPE_6__ {scalar_t__ band; } ;
struct TYPE_5__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDING_CONTEXT_CMD ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_CTXT_ACTION_ADD ; 
 int /*<<< orphan*/  FW_CTXT_INVALID ; 
 int IWL_BINDING_CMD_SIZE_V1 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_LMAC_24G_INDEX ; 
 int /*<<< orphan*/  IWL_LMAC_5G_INDEX ; 
 int /*<<< orphan*/  IWL_MVM_MAX_QUOTA ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_BINDING_CDB_SUPPORT ; 
 int MAX_BINDINGS ; 
 int MAX_MACS_IN_BINDING ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  TIME_QUOTA_CMD ; 
 scalar_t__ WARN_ON (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_init_fw_regd (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_is_cdb_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_lar_supported (struct iwl_mvm*) ; 
 int iwl_mvm_mac_ctxt_add (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ *) ; 
 int iwl_mvm_phy_ctxt_add (struct iwl_mvm*,TYPE_4__*,struct cfg80211_chan_def*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_time_quota_data* iwl_mvm_quota_cmd_get_quota (struct iwl_mvm*,struct iwl_time_quota_cmd*,int) ; 
 int /*<<< orphan*/  iwl_mvm_quota_cmd_size (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_time_quota_cmd*) ; 
 int iwl_mvm_send_cmd_pdu_status (struct iwl_mvm*,int /*<<< orphan*/ ,int,struct iwl_binding_cmd*,int*) ; 
 int iwl_mvm_sta_send_to_fw (struct iwl_mvm*,struct ieee80211_sta*,int,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_sta*) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int iwl_mvm_d3_reprogram(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
				struct ieee80211_sta *ap_sta)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct ieee80211_chanctx_conf *ctx;
	u8 chains_static, chains_dynamic;
	struct cfg80211_chan_def chandef;
	int ret, i;
	struct iwl_binding_cmd binding_cmd = {};
	struct iwl_time_quota_cmd quota_cmd = {};
	struct iwl_time_quota_data *quota;
	u32 status;
	int size;

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_BINDING_CDB_SUPPORT)) {
		size = sizeof(binding_cmd);
		if (mvmvif->phy_ctxt->channel->band == NL80211_BAND_2GHZ ||
		    !iwl_mvm_is_cdb_supported(mvm))
			binding_cmd.lmac_id = cpu_to_le32(IWL_LMAC_24G_INDEX);
		else
			binding_cmd.lmac_id = cpu_to_le32(IWL_LMAC_5G_INDEX);
	} else {
		size = IWL_BINDING_CMD_SIZE_V1;
	}

	/* add back the PHY */
	if (WARN_ON(!mvmvif->phy_ctxt))
		return -EINVAL;

	rcu_read_lock();
	ctx = rcu_dereference(vif->chanctx_conf);
	if (WARN_ON(!ctx)) {
		rcu_read_unlock();
		return -EINVAL;
	}
	chandef = ctx->def;
	chains_static = ctx->rx_chains_static;
	chains_dynamic = ctx->rx_chains_dynamic;
	rcu_read_unlock();

	ret = iwl_mvm_phy_ctxt_add(mvm, mvmvif->phy_ctxt, &chandef,
				   chains_static, chains_dynamic);
	if (ret)
		return ret;

	/* add back the MAC */
	mvmvif->uploaded = false;

	if (WARN_ON(!vif->bss_conf.assoc))
		return -EINVAL;

	ret = iwl_mvm_mac_ctxt_add(mvm, vif);
	if (ret)
		return ret;

	/* add back binding - XXX refactor? */
	binding_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->phy_ctxt->id,
						mvmvif->phy_ctxt->color));
	binding_cmd.action = cpu_to_le32(FW_CTXT_ACTION_ADD);
	binding_cmd.phy =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->phy_ctxt->id,
						mvmvif->phy_ctxt->color));
	binding_cmd.macs[0] = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->id,
							      mvmvif->color));
	for (i = 1; i < MAX_MACS_IN_BINDING; i++)
		binding_cmd.macs[i] = cpu_to_le32(FW_CTXT_INVALID);

	status = 0;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, BINDING_CONTEXT_CMD,
					  size, &binding_cmd, &status);
	if (ret) {
		IWL_ERR(mvm, "Failed to add binding: %d\n", ret);
		return ret;
	}

	if (status) {
		IWL_ERR(mvm, "Binding command failed: %u\n", status);
		return -EIO;
	}

	ret = iwl_mvm_sta_send_to_fw(mvm, ap_sta, false, 0);
	if (ret)
		return ret;
	rcu_assign_pointer(mvm->fw_id_to_mac_id[mvmvif->ap_sta_id], ap_sta);

	ret = iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);
	if (ret)
		return ret;

	/* and some quota */
	quota = iwl_mvm_quota_cmd_get_quota(mvm, &quota_cmd, 0);
	quota->id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->phy_ctxt->id,
						mvmvif->phy_ctxt->color));
	quota->quota = cpu_to_le32(IWL_MVM_MAX_QUOTA);
	quota->max_duration = cpu_to_le32(IWL_MVM_MAX_QUOTA);

	for (i = 1; i < MAX_BINDINGS; i++) {
		quota = iwl_mvm_quota_cmd_get_quota(mvm, &quota_cmd, i);
		quota->id_and_color = cpu_to_le32(FW_CTXT_INVALID);
	}

	ret = iwl_mvm_send_cmd_pdu(mvm, TIME_QUOTA_CMD, 0,
				   iwl_mvm_quota_cmd_size(mvm), &quota_cmd);
	if (ret)
		IWL_ERR(mvm, "Failed to send quota: %d\n", ret);

	if (iwl_mvm_is_lar_supported(mvm) && iwl_mvm_init_fw_regd(mvm))
		IWL_ERR(mvm, "Failed to initialize D3 LAR information\n");

	return 0;
}
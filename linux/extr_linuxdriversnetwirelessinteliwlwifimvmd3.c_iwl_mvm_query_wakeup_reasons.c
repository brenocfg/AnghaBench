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
typedef  int u16 ;
struct iwl_wowlan_status_data {int* qos_seq_ctr; int /*<<< orphan*/  wake_packet; void* wake_packet_bufsize; void* wake_packet_length; void* wakeup_reasons; void* pattern_number; } ;
struct iwl_wowlan_status {int /*<<< orphan*/  wake_packet; int /*<<< orphan*/  wake_packet_bufsize; int /*<<< orphan*/  wake_packet_length; int /*<<< orphan*/  wakeup_reasons; int /*<<< orphan*/ * qos_seq_ctr; int /*<<< orphan*/  pattern_number; } ;
struct iwl_mvm_sta {TYPE_1__* tid_data; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_2__ {int seq_number; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct iwl_wowlan_status*) ; 
 int IWL_MAX_TID_COUNT ; 
 struct iwl_wowlan_status* iwl_mvm_get_wakeup_status (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_report_wakeup_reasons (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_wowlan_status_data*) ; 
 int iwl_mvm_setup_connection_keep (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_wowlan_status*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_staid_protected (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iwl_wowlan_status*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool iwl_mvm_query_wakeup_reasons(struct iwl_mvm *mvm,
					 struct ieee80211_vif *vif)
{
	struct iwl_wowlan_status_data status;
	struct iwl_wowlan_status *fw_status;
	int i;
	bool keep;
	struct iwl_mvm_sta *mvm_ap_sta;

	fw_status = iwl_mvm_get_wakeup_status(mvm, vif);
	if (IS_ERR_OR_NULL(fw_status))
		goto out_unlock;

	status.pattern_number = le16_to_cpu(fw_status->pattern_number);
	for (i = 0; i < 8; i++)
		status.qos_seq_ctr[i] =
			le16_to_cpu(fw_status->qos_seq_ctr[i]);
	status.wakeup_reasons = le32_to_cpu(fw_status->wakeup_reasons);
	status.wake_packet_length =
		le32_to_cpu(fw_status->wake_packet_length);
	status.wake_packet_bufsize =
		le32_to_cpu(fw_status->wake_packet_bufsize);
	status.wake_packet = fw_status->wake_packet;

	/* still at hard-coded place 0 for D3 image */
	mvm_ap_sta = iwl_mvm_sta_from_staid_protected(mvm, 0);
	if (!mvm_ap_sta)
		goto out_free;

	for (i = 0; i < IWL_MAX_TID_COUNT; i++) {
		u16 seq = status.qos_seq_ctr[i];
		/* firmware stores last-used value, we store next value */
		seq += 0x10;
		mvm_ap_sta->tid_data[i].seq_number = seq;
	}

	/* now we have all the data we need, unlock to avoid mac80211 issues */
	mutex_unlock(&mvm->mutex);

	iwl_mvm_report_wakeup_reasons(mvm, vif, &status);

	keep = iwl_mvm_setup_connection_keep(mvm, vif, fw_status);

	kfree(fw_status);
	return keep;

out_free:
	kfree(fw_status);
out_unlock:
	mutex_unlock(&mvm->mutex);
	return false;
}
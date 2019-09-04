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
struct iwl_time_event_cmd {int repeat; int /*<<< orphan*/  policy; void* duration; void* max_delay; int /*<<< orphan*/  max_frags; void* interval; void* apply_time; void* id; void* id_and_color; void* action; } ;
struct iwl_mvm_time_event_data {scalar_t__ running; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  color; int /*<<< orphan*/  id; struct iwl_mvm_time_event_data time_event_data; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum ieee80211_roc_type { ____Placeholder_ieee80211_roc_type } ieee80211_roc_type ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FW_CTXT_ACTION_ADD ; 
#define  IEEE80211_ROC_TYPE_MGMT_TX 129 
#define  IEEE80211_ROC_TYPE_NORMAL 128 
 int IWL_MVM_ROC_TE_TYPE_MGMT_TX ; 
 int IWL_MVM_ROC_TE_TYPE_NORMAL ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
 int MSEC_TO_TU (int) ; 
 int /*<<< orphan*/  TE_V2_FRAG_ENDLESS ; 
 int TE_V2_NOTIF_HOST_EVENT_END ; 
 int TE_V2_NOTIF_HOST_EVENT_START ; 
 int TE_V2_START_IMMEDIATELY ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int iwl_mvm_time_event_send_add (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_mvm_time_event_data*,struct iwl_time_event_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 

int iwl_mvm_start_p2p_roc(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			  int duration, enum ieee80211_roc_type type)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_time_event_data *te_data = &mvmvif->time_event_data;
	struct iwl_time_event_cmd time_cmd = {};

	lockdep_assert_held(&mvm->mutex);
	if (te_data->running) {
		IWL_WARN(mvm, "P2P_DEVICE remain on channel already running\n");
		return -EBUSY;
	}

	time_cmd.action = cpu_to_le32(FW_CTXT_ACTION_ADD);
	time_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->id, mvmvif->color));

	switch (type) {
	case IEEE80211_ROC_TYPE_NORMAL:
		time_cmd.id = cpu_to_le32(IWL_MVM_ROC_TE_TYPE_NORMAL);
		break;
	case IEEE80211_ROC_TYPE_MGMT_TX:
		time_cmd.id = cpu_to_le32(IWL_MVM_ROC_TE_TYPE_MGMT_TX);
		break;
	default:
		WARN_ONCE(1, "Got an invalid ROC type\n");
		return -EINVAL;
	}

	time_cmd.apply_time = cpu_to_le32(0);
	time_cmd.interval = cpu_to_le32(1);

	/*
	 * The P2P Device TEs can have lower priority than other events
	 * that are being scheduled by the driver/fw, and thus it might not be
	 * scheduled. To improve the chances of it being scheduled, allow them
	 * to be fragmented, and in addition allow them to be delayed.
	 */
	time_cmd.max_frags = min(MSEC_TO_TU(duration)/50, TE_V2_FRAG_ENDLESS);
	time_cmd.max_delay = cpu_to_le32(MSEC_TO_TU(duration/2));
	time_cmd.duration = cpu_to_le32(MSEC_TO_TU(duration));
	time_cmd.repeat = 1;
	time_cmd.policy = cpu_to_le16(TE_V2_NOTIF_HOST_EVENT_START |
				      TE_V2_NOTIF_HOST_EVENT_END |
				      TE_V2_START_IMMEDIATELY);

	return iwl_mvm_time_event_send_add(mvm, vif, te_data, &time_cmd);
}
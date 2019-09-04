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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_time_event_cmd {int repeat; int /*<<< orphan*/  policy; void* duration; void* interval; void* max_delay; int /*<<< orphan*/  max_frags; void* apply_time; void* id; void* id_and_color; void* action; } ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm_time_event_data {scalar_t__ end_jiffies; int /*<<< orphan*/  uid; scalar_t__ running; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  color; int /*<<< orphan*/  id; struct iwl_mvm_time_event_data time_event_data; } ;
struct iwl_mvm {int /*<<< orphan*/  notif_wait; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FW_CTXT_ACTION_ADD ; 
 int /*<<< orphan*/  IWL_DEBUG_TE (struct iwl_mvm*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int TE_BSS_STA_AGGRESSIVE_ASSOC ; 
 int /*<<< orphan*/  TE_V2_FRAG_NONE ; 
 int TE_V2_NOTIF_HOST_EVENT_END ; 
 int TE_V2_NOTIF_HOST_EVENT_START ; 
 int TE_V2_START_IMMEDIATELY ; 
 int /*<<< orphan*/  const TIME_EVENT_NOTIFICATION ; 
 int /*<<< orphan*/  TU_TO_EXP_TIME (int) ; 
 int /*<<< orphan*/  TU_TO_JIFFIES (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_time_event_data*) ; 
 int /*<<< orphan*/  iwl_mvm_stop_session_protection (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_te_notif ; 
 scalar_t__ iwl_mvm_time_event_send_add (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_mvm_time_event_data*,struct iwl_time_event_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 scalar_t__ iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,int /*<<< orphan*/ ) ; 

void iwl_mvm_protect_session(struct iwl_mvm *mvm,
			     struct ieee80211_vif *vif,
			     u32 duration, u32 min_duration,
			     u32 max_delay, bool wait_for_notif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_time_event_data *te_data = &mvmvif->time_event_data;
	const u16 te_notif_response[] = { TIME_EVENT_NOTIFICATION };
	struct iwl_notification_wait wait_te_notif;
	struct iwl_time_event_cmd time_cmd = {};

	lockdep_assert_held(&mvm->mutex);

	if (te_data->running &&
	    time_after(te_data->end_jiffies, TU_TO_EXP_TIME(min_duration))) {
		IWL_DEBUG_TE(mvm, "We have enough time in the current TE: %u\n",
			     jiffies_to_msecs(te_data->end_jiffies - jiffies));
		return;
	}

	if (te_data->running) {
		IWL_DEBUG_TE(mvm, "extend 0x%x: only %u ms left\n",
			     te_data->uid,
			     jiffies_to_msecs(te_data->end_jiffies - jiffies));
		/*
		 * we don't have enough time
		 * cancel the current TE and issue a new one
		 * Of course it would be better to remove the old one only
		 * when the new one is added, but we don't care if we are off
		 * channel for a bit. All we need to do, is not to return
		 * before we actually begin to be on the channel.
		 */
		iwl_mvm_stop_session_protection(mvm, vif);
	}

	time_cmd.action = cpu_to_le32(FW_CTXT_ACTION_ADD);
	time_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->id, mvmvif->color));
	time_cmd.id = cpu_to_le32(TE_BSS_STA_AGGRESSIVE_ASSOC);

	time_cmd.apply_time = cpu_to_le32(0);

	time_cmd.max_frags = TE_V2_FRAG_NONE;
	time_cmd.max_delay = cpu_to_le32(max_delay);
	/* TODO: why do we need to interval = bi if it is not periodic? */
	time_cmd.interval = cpu_to_le32(1);
	time_cmd.duration = cpu_to_le32(duration);
	time_cmd.repeat = 1;
	time_cmd.policy = cpu_to_le16(TE_V2_NOTIF_HOST_EVENT_START |
				      TE_V2_NOTIF_HOST_EVENT_END |
				      TE_V2_START_IMMEDIATELY);

	if (!wait_for_notif) {
		iwl_mvm_time_event_send_add(mvm, vif, te_data, &time_cmd);
		return;
	}

	/*
	 * Create notification_wait for the TIME_EVENT_NOTIFICATION to use
	 * right after we send the time event
	 */
	iwl_init_notification_wait(&mvm->notif_wait, &wait_te_notif,
				   te_notif_response,
				   ARRAY_SIZE(te_notif_response),
				   iwl_mvm_te_notif, te_data);

	/* If TE was sent OK - wait for the notification that started */
	if (iwl_mvm_time_event_send_add(mvm, vif, te_data, &time_cmd)) {
		IWL_ERR(mvm, "Failed to add TE to protect session\n");
		iwl_remove_notification(&mvm->notif_wait, &wait_te_notif);
	} else if (iwl_wait_notification(&mvm->notif_wait, &wait_te_notif,
					 TU_TO_JIFFIES(max_delay))) {
		IWL_ERR(mvm, "Failed to protect session until TE\n");
	}
}
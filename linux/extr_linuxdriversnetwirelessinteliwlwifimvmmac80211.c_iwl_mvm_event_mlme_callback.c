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
struct iwl_mvm {int /*<<< orphan*/  fwrt; int /*<<< orphan*/  fw; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct iwl_fw_dbg_trigger_mlme {scalar_t__ stop_tx_deauth; scalar_t__ stop_rx_deauth; scalar_t__ stop_auth_timeout; scalar_t__ stop_auth_denied; scalar_t__ stop_assoc_timeout; scalar_t__ stop_assoc_denied; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_3__ {scalar_t__ data; scalar_t__ status; int /*<<< orphan*/  reason; } ;
struct TYPE_4__ {TYPE_1__ mlme; } ;
struct ieee80211_event {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ ASSOC_EVENT ; 
 scalar_t__ AUTH_EVENT ; 
 scalar_t__ DEAUTH_RX_EVENT ; 
 scalar_t__ DEAUTH_TX_EVENT ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_MLME ; 
 scalar_t__ MLME_DENIED ; 
 scalar_t__ MLME_TIMEOUT ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*,char*,...) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_get_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_check_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iwl_fw_dbg_trigger_tlv*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_event_mlme_callback(struct iwl_mvm *mvm,
					struct ieee80211_vif *vif,
					const struct ieee80211_event *event)
{
#define CHECK_MLME_TRIGGER(_cnt, _fmt...)				\
	do {								\
		if ((trig_mlme->_cnt) && --(trig_mlme->_cnt))		\
			break;						\
		iwl_fw_dbg_collect_trig(&(mvm)->fwrt, trig, _fmt);	\
	} while (0)

	struct iwl_fw_dbg_trigger_tlv *trig;
	struct iwl_fw_dbg_trigger_mlme *trig_mlme;

	if (!iwl_fw_dbg_trigger_enabled(mvm->fw, FW_DBG_TRIGGER_MLME))
		return;

	trig = iwl_fw_dbg_get_trigger(mvm->fw, FW_DBG_TRIGGER_MLME);
	trig_mlme = (void *)trig->data;
	if (!iwl_fw_dbg_trigger_check_stop(&mvm->fwrt,
					   ieee80211_vif_to_wdev(vif), trig))
		return;

	if (event->u.mlme.data == ASSOC_EVENT) {
		if (event->u.mlme.status == MLME_DENIED)
			CHECK_MLME_TRIGGER(stop_assoc_denied,
					   "DENIED ASSOC: reason %d",
					    event->u.mlme.reason);
		else if (event->u.mlme.status == MLME_TIMEOUT)
			CHECK_MLME_TRIGGER(stop_assoc_timeout,
					   "ASSOC TIMEOUT");
	} else if (event->u.mlme.data == AUTH_EVENT) {
		if (event->u.mlme.status == MLME_DENIED)
			CHECK_MLME_TRIGGER(stop_auth_denied,
					   "DENIED AUTH: reason %d",
					   event->u.mlme.reason);
		else if (event->u.mlme.status == MLME_TIMEOUT)
			CHECK_MLME_TRIGGER(stop_auth_timeout,
					   "AUTH TIMEOUT");
	} else if (event->u.mlme.data == DEAUTH_RX_EVENT) {
		CHECK_MLME_TRIGGER(stop_rx_deauth,
				   "DEAUTH RX %d", event->u.mlme.reason);
	} else if (event->u.mlme.data == DEAUTH_TX_EVENT) {
		CHECK_MLME_TRIGGER(stop_tx_deauth,
				   "DEAUTH TX %d", event->u.mlme.reason);
	}
#undef CHECK_MLME_TRIGGER
}
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
typedef  int u32 ;
struct iwl_mvm {int /*<<< orphan*/  fwrt; int /*<<< orphan*/  fw; } ;
struct iwl_fw_dbg_trigger_tx_status {TYPE_1__* statuses; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_TX_STATUS ; 
 int TX_STATUS_MSK ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*,char*,int) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_get_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_check_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_tx_status_check_trigger(struct iwl_mvm *mvm,
					    u32 status)
{
	struct iwl_fw_dbg_trigger_tlv *trig;
	struct iwl_fw_dbg_trigger_tx_status *status_trig;
	int i;

	if (!iwl_fw_dbg_trigger_enabled(mvm->fw, FW_DBG_TRIGGER_TX_STATUS))
		return;

	trig = iwl_fw_dbg_get_trigger(mvm->fw, FW_DBG_TRIGGER_TX_STATUS);
	status_trig = (void *)trig->data;

	if (!iwl_fw_dbg_trigger_check_stop(&mvm->fwrt, NULL, trig))
		return;

	for (i = 0; i < ARRAY_SIZE(status_trig->statuses); i++) {
		/* don't collect on status 0 */
		if (!status_trig->statuses[i].status)
			break;

		if (status_trig->statuses[i].status != (status & TX_STATUS_MSK))
			continue;

		iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
					"Tx status %d was received",
					status & TX_STATUS_MSK);
		break;
	}
}
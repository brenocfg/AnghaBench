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
struct iwl_mvm_reprobe {int /*<<< orphan*/  work; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {scalar_t__ fw_restart; int /*<<< orphan*/  hw; int /*<<< orphan*/  status; scalar_t__ hw_registered; TYPE_2__ fwrt; TYPE_1__* trans; int /*<<< orphan*/  notif_wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_REF_UCODE_DOWN ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RESTART_REQUESTED ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 scalar_t__ IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ieee80211_restart_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_abort_notification_waits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_dump_desc_assert ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_desc (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_ref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_report_scan_aborted (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_reprobe_wk ; 
 struct iwl_mvm_reprobe* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

void iwl_mvm_nic_restart(struct iwl_mvm *mvm, bool fw_error)
{
	iwl_abort_notification_waits(&mvm->notif_wait);

	/*
	 * This is a bit racy, but worst case we tell mac80211 about
	 * a stopped/aborted scan when that was already done which
	 * is not a problem. It is necessary to abort any os scan
	 * here because mac80211 requires having the scan cleared
	 * before restarting.
	 * We'll reset the scan_status to NONE in restart cleanup in
	 * the next start() call from mac80211. If restart isn't called
	 * (no fw restart) scan status will stay busy.
	 */
	iwl_mvm_report_scan_aborted(mvm);

	/*
	 * If we're restarting already, don't cycle restarts.
	 * If INIT fw asserted, it will likely fail again.
	 * If WoWLAN fw asserted, don't restart either, mac80211
	 * can't recover this since we're already half suspended.
	 */
	if (!mvm->fw_restart && fw_error) {
		iwl_fw_dbg_collect_desc(&mvm->fwrt, &iwl_dump_desc_assert,
					NULL);
	} else if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) {
		struct iwl_mvm_reprobe *reprobe;

		IWL_ERR(mvm,
			"Firmware error during reconfiguration - reprobe!\n");

		/*
		 * get a module reference to avoid doing this while unloading
		 * anyway and to avoid scheduling a work with code that's
		 * being removed.
		 */
		if (!try_module_get(THIS_MODULE)) {
			IWL_ERR(mvm, "Module is being unloaded - abort\n");
			return;
		}

		reprobe = kzalloc(sizeof(*reprobe), GFP_ATOMIC);
		if (!reprobe) {
			module_put(THIS_MODULE);
			return;
		}
		reprobe->dev = mvm->trans->dev;
		INIT_WORK(&reprobe->work, iwl_mvm_reprobe_wk);
		schedule_work(&reprobe->work);
	} else if (mvm->fwrt.cur_fw_img == IWL_UCODE_REGULAR &&
		   mvm->hw_registered) {
		/* don't let the transport/FW power down */
		iwl_mvm_ref(mvm, IWL_MVM_REF_UCODE_DOWN);

		if (fw_error && mvm->fw_restart > 0)
			mvm->fw_restart--;
		set_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status);
		ieee80211_restart_hw(mvm->hw);
	}
}
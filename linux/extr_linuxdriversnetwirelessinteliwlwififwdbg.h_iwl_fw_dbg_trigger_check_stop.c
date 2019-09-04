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
struct wireless_dev {int dummy; } ;
struct iwl_fw_runtime {int dummy; } ;
struct iwl_fw_dbg_trigger_tlv {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_WARN (struct iwl_fw_runtime*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_fw_dbg_no_trig_window (struct iwl_fw_runtime*,struct iwl_fw_dbg_trigger_tlv*) ; 
 int iwl_fw_dbg_trigger_stop_conf_match (struct iwl_fw_runtime*,struct iwl_fw_dbg_trigger_tlv*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_vif_match (struct iwl_fw_dbg_trigger_tlv*,struct wireless_dev*) ; 

__attribute__((used)) static inline bool
iwl_fw_dbg_trigger_check_stop(struct iwl_fw_runtime *fwrt,
			      struct wireless_dev *wdev,
			      struct iwl_fw_dbg_trigger_tlv *trig)
{
	if (wdev && !iwl_fw_dbg_trigger_vif_match(trig, wdev))
		return false;

	if (iwl_fw_dbg_no_trig_window(fwrt, trig)) {
		IWL_WARN(fwrt, "Trigger %d occurred while no-collect window.\n",
			 trig->id);
		return false;
	}

	return iwl_fw_dbg_trigger_stop_conf_match(fwrt, trig);
}
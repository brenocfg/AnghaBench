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
struct TYPE_4__ {int /*<<< orphan*/  cur_fw_img; } ;
struct iwl_mvm {TYPE_2__ fwrt; int /*<<< orphan*/  trans; } ;
struct TYPE_3__ {scalar_t__ init_dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_UCODE_REGULAR ; 
 int _iwl_trans_start_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _iwl_trans_stop_device (int /*<<< orphan*/ ,int) ; 
 int iwl_init_paging (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_unified_ucode (struct iwl_mvm*) ; 
 int iwl_mvm_load_ucode_wait_alive (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_run_init_mvm_ucode (struct iwl_mvm*,int) ; 
 int iwl_run_unified_mvm_ucode (struct iwl_mvm*,int) ; 
 TYPE_1__ iwlmvm_mod_params ; 

__attribute__((used)) static int iwl_mvm_load_rt_fw(struct iwl_mvm *mvm)
{
	int ret;

	if (iwl_mvm_has_unified_ucode(mvm))
		return iwl_run_unified_mvm_ucode(mvm, false);

	ret = iwl_run_init_mvm_ucode(mvm, false);

	if (ret) {
		IWL_ERR(mvm, "Failed to run INIT ucode: %d\n", ret);

		if (iwlmvm_mod_params.init_dbg)
			return 0;
		return ret;
	}

	/*
	 * Stop and start the transport without entering low power
	 * mode. This will save the state of other components on the
	 * device that are triggered by the INIT firwmare (MFUART).
	 */
	_iwl_trans_stop_device(mvm->trans, false);
	ret = _iwl_trans_start_hw(mvm->trans, false);
	if (ret)
		return ret;

	ret = iwl_mvm_load_ucode_wait_alive(mvm, IWL_UCODE_REGULAR);
	if (ret)
		return ret;

	return iwl_init_paging(&mvm->fwrt, mvm->fwrt.cur_fw_img);
}
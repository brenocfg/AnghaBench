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
struct TYPE_2__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {TYPE_1__ fwrt; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t EIO ; 
 scalar_t__ IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  iwl_mvm_enter_ctkill (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_force_ctkill_write(struct iwl_mvm *mvm, char *buf,
					    size_t count, loff_t *ppos)
{
	if (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR)
		return -EIO;

	iwl_mvm_enter_ctkill(mvm);

	return count;
}
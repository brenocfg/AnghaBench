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
struct iwl_mvm {int /*<<< orphan*/  trans; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IWL_MVM_REF_NMI ; 
 int /*<<< orphan*/  iwl_force_nmi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int iwl_mvm_ref_sync (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_fw_nmi_write(struct iwl_mvm *mvm, char *buf,
				      size_t count, loff_t *ppos)
{
	int ret;

	if (!iwl_mvm_firmware_running(mvm))
		return -EIO;

	ret = iwl_mvm_ref_sync(mvm, IWL_MVM_REF_NMI);
	if (ret)
		return ret;

	iwl_force_nmi(mvm->trans);

	iwl_mvm_unref(mvm, IWL_MVM_REF_NMI);

	return count;
}
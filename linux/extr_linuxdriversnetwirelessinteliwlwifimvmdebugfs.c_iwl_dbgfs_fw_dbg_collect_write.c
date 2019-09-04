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
struct iwl_mvm {int /*<<< orphan*/  fwrt; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DBG_TRIGGER_USER ; 
 int /*<<< orphan*/  IWL_MVM_REF_PRPH_WRITE ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *) ; 
 int iwl_mvm_ref_sync (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_fw_dbg_collect_write(struct iwl_mvm *mvm,
					      char *buf, size_t count,
					      loff_t *ppos)
{
	int ret;

	ret = iwl_mvm_ref_sync(mvm, IWL_MVM_REF_PRPH_WRITE);
	if (ret)
		return ret;
	if (count == 0)
		return 0;

	iwl_fw_dbg_collect(&mvm->fwrt, FW_DBG_TRIGGER_USER, buf,
			   (count - 1), NULL);

	iwl_mvm_unref(mvm, IWL_MVM_REF_PRPH_WRITE);

	return count;
}
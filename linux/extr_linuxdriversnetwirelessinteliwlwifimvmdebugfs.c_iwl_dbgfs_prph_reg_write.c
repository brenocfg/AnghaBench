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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int /*<<< orphan*/  dbgfs_prph_reg_addr; int /*<<< orphan*/  trans; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_MVM_REF_PRPH_WRITE ; 
 int iwl_mvm_ref_sync (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_prph (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
iwl_dbgfs_prph_reg_write(struct iwl_mvm *mvm, char *buf,
			 size_t count, loff_t *ppos)
{
	u8 args;
	u32 value;
	int ret;

	args = sscanf(buf, "%i %i", &mvm->dbgfs_prph_reg_addr, &value);
	/* if we only want to set the reg address - nothing more to do */
	if (args == 1)
		goto out;

	/* otherwise, make sure we have both address and value */
	if (args != 2)
		return -EINVAL;

	ret = iwl_mvm_ref_sync(mvm, IWL_MVM_REF_PRPH_WRITE);
	if (ret)
		return ret;

	iwl_write_prph(mvm->trans, mvm->dbgfs_prph_reg_addr, value);

	iwl_mvm_unref(mvm, IWL_MVM_REF_PRPH_WRITE);
out:
	return count;
}
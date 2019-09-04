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
struct iwl_mvm {int* refs; int /*<<< orphan*/  mutex; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t IWL_MVM_REF_USER ; 
 int /*<<< orphan*/  iwl_mvm_ref (struct iwl_mvm*,size_t) ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,size_t) ; 
 int kstrtoul (char*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_d0i3_refs_write(struct iwl_mvm *mvm, char *buf,
					 size_t count, loff_t *ppos)
{
	unsigned long value;
	int ret;
	bool taken;

	ret = kstrtoul(buf, 10, &value);
	if (ret < 0)
		return ret;

	mutex_lock(&mvm->mutex);

	taken = mvm->refs[IWL_MVM_REF_USER];
	if (value == 1 && !taken)
		iwl_mvm_ref(mvm, IWL_MVM_REF_USER);
	else if (value == 0 && taken)
		iwl_mvm_unref(mvm, IWL_MVM_REF_USER);
	else
		ret = -EINVAL;

	mutex_unlock(&mvm->mutex);

	if (ret < 0)
		return ret;
	return count;
}
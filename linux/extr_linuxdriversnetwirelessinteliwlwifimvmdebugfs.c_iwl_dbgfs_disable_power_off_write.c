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
struct iwl_mvm {int disable_power_off; int disable_power_off_d3; int /*<<< orphan*/  mutex; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int iwl_mvm_power_update_device (struct iwl_mvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_disable_power_off_write(struct iwl_mvm *mvm, char *buf,
						 size_t count, loff_t *ppos)
{
	int ret, val;

	if (!iwl_mvm_firmware_running(mvm))
		return -EIO;

	if (!strncmp("disable_power_off_d0=", buf, 21)) {
		if (sscanf(buf + 21, "%d", &val) != 1)
			return -EINVAL;
		mvm->disable_power_off = val;
	} else if (!strncmp("disable_power_off_d3=", buf, 21)) {
		if (sscanf(buf + 21, "%d", &val) != 1)
			return -EINVAL;
		mvm->disable_power_off_d3 = val;
	} else {
		return -EINVAL;
	}

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_power_update_device(mvm);
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}
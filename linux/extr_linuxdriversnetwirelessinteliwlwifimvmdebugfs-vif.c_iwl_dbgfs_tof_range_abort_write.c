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
struct iwl_mvm_vif {struct iwl_mvm* mvm; } ;
struct TYPE_2__ {int last_abort_id; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_1__ tof_data; } ;
struct ieee80211_vif {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 char* iwl_dbgfs_is_match (char*,char*) ; 
 int iwl_mvm_tof_range_abort_cmd (struct iwl_mvm*,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int kstrtou32 (char*,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_tof_range_abort_write(struct ieee80211_vif *vif,
					       char *buf,
					       size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	u32 value;
	int abort_id, ret = 0;
	char *data;

	mutex_lock(&mvm->mutex);

	data = iwl_dbgfs_is_match("abort_id=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.last_abort_id = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("send_range_abort=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0 && value) {
			abort_id = mvm->tof_data.last_abort_id;
			ret = iwl_mvm_tof_range_abort_cmd(mvm, abort_id);
			goto out;
		}
	}

out:
	mutex_unlock(&mvm->mutex);
	return ret ?: count;
}
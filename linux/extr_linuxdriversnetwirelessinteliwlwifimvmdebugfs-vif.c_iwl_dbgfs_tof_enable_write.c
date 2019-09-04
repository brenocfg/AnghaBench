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
typedef  void* u32 ;
struct iwl_mvm_vif {struct iwl_mvm* mvm; } ;
struct TYPE_3__ {void* is_buf_required; void* is_debug_mode; void* one_sided_disabled; void* tof_disabled; } ;
struct TYPE_4__ {TYPE_1__ tof_cfg; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_2__ tof_data; } ;
struct ieee80211_vif {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 char* iwl_dbgfs_is_match (char*,char*) ; 
 int iwl_mvm_tof_config_cmd (struct iwl_mvm*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int kstrtou32 (char*,int,void**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_tof_enable_write(struct ieee80211_vif *vif,
					  char *buf,
					  size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	u32 value;
	int ret = -EINVAL;
	char *data;

	mutex_lock(&mvm->mutex);

	data = iwl_dbgfs_is_match("tof_disabled=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.tof_cfg.tof_disabled = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("one_sided_disabled=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.tof_cfg.one_sided_disabled = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("is_debug_mode=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.tof_cfg.is_debug_mode = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("is_buf=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.tof_cfg.is_buf_required = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("send_tof_cfg=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0 && value) {
			ret = iwl_mvm_tof_config_cmd(mvm);
			goto out;
		}
	}

out:
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}
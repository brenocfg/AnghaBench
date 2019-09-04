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
struct TYPE_3__ {void* ftm_format_and_bw80M; void* ftm_format_and_bw40M; void* ftm_format_and_bw20M; void* min_delta_ftm; int /*<<< orphan*/  tsf_timer_offset_msec; } ;
struct TYPE_4__ {TYPE_1__ range_req_ext; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_2__ tof_data; } ;
struct ieee80211_vif {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le16 (void*) ; 
 char* iwl_dbgfs_is_match (char*,char*) ; 
 int iwl_mvm_tof_range_request_ext_cmd (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int kstrtou32 (char*,int,void**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_tof_range_req_ext_write(struct ieee80211_vif *vif,
						 char *buf,
						 size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	u32 value;
	int ret = 0;
	char *data;

	mutex_lock(&mvm->mutex);

	data = iwl_dbgfs_is_match("tsf_timer_offset_msec=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req_ext.tsf_timer_offset_msec =
							cpu_to_le16(value);
		goto out;
	}

	data = iwl_dbgfs_is_match("min_delta_ftm=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req_ext.min_delta_ftm = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("ftm_format_and_bw20M=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req_ext.ftm_format_and_bw20M =
									value;
		goto out;
	}

	data = iwl_dbgfs_is_match("ftm_format_and_bw40M=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req_ext.ftm_format_and_bw40M =
									value;
		goto out;
	}

	data = iwl_dbgfs_is_match("ftm_format_and_bw80M=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req_ext.ftm_format_and_bw80M =
									value;
		goto out;
	}

	data = iwl_dbgfs_is_match("send_range_req_ext=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0 && value)
			ret = iwl_mvm_tof_range_request_ext_cmd(mvm, vif);
		goto out;
	}

	ret = -EINVAL;
out:
	mutex_unlock(&mvm->mutex);
	return ret ?: count;
}
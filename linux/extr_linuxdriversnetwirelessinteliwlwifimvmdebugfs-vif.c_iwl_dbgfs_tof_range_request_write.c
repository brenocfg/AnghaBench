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
struct iwl_tof_range_req_ap_entry {int /*<<< orphan*/  burst_period; int /*<<< orphan*/  rssi; int /*<<< orphan*/  enable_dyn_ack; int /*<<< orphan*/  asap_mode; int /*<<< orphan*/  location_req; int /*<<< orphan*/  tsf_delta; int /*<<< orphan*/  retries_per_sample; int /*<<< orphan*/  samples_per_burst; int /*<<< orphan*/  num_of_bursts; int /*<<< orphan*/  measure_type; int /*<<< orphan*/  ctrl_ch_position; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  channel_num; struct iwl_tof_range_req_ap_entry* bssid; } ;
typedef  struct iwl_tof_range_req_ap_entry u8 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm_vif {struct iwl_mvm* mvm; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ap; int /*<<< orphan*/ * macaddr_mask; int /*<<< orphan*/ * macaddr_template; void* num_of_ap; void* macaddr_random; void* report_policy; void* req_timeout; void* one_sided_los_disable; void* initiator; void* request_id; } ;
struct TYPE_4__ {TYPE_1__ range_req; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_2__ tof_data; } ;
struct ieee80211_vif {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,unsigned int) ; 
 unsigned int IWL_MVM_TOF_MAX_APS ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 char* iwl_dbgfs_is_match (char*,char*) ; 
 int iwl_mvm_tof_range_request_cmd (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int kstrtou32 (char*,int,void**) ; 
 int /*<<< orphan*/  mac_pton (char*,struct iwl_tof_range_req_ap_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iwl_tof_range_req_ap_entry*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct iwl_tof_range_req_ap_entry*,struct iwl_tof_range_req_ap_entry*,struct iwl_tof_range_req_ap_entry*,struct iwl_tof_range_req_ap_entry*,struct iwl_tof_range_req_ap_entry*,struct iwl_tof_range_req_ap_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_tof_range_request_write(struct ieee80211_vif *vif,
						 char *buf, size_t count,
						 loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	u32 value;
	int ret = 0;
	char *data;

	mutex_lock(&mvm->mutex);

	data = iwl_dbgfs_is_match("request_id=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req.request_id = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("initiator=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req.initiator = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("one_sided_los_disable=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req.one_sided_los_disable = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("req_timeout=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req.req_timeout = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("report_policy=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req.report_policy = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("macaddr_random=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req.macaddr_random = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("num_of_ap=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.range_req.num_of_ap = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("macaddr_template=", buf);
	if (data) {
		u8 mac[ETH_ALEN];

		if (!mac_pton(data, mac)) {
			ret = -EINVAL;
			goto out;
		}
		memcpy(mvm->tof_data.range_req.macaddr_template, mac, ETH_ALEN);
		goto out;
	}

	data = iwl_dbgfs_is_match("macaddr_mask=", buf);
	if (data) {
		u8 mac[ETH_ALEN];

		if (!mac_pton(data, mac)) {
			ret = -EINVAL;
			goto out;
		}
		memcpy(mvm->tof_data.range_req.macaddr_mask, mac, ETH_ALEN);
		goto out;
	}

	data = iwl_dbgfs_is_match("ap=", buf);
	if (data) {
		struct iwl_tof_range_req_ap_entry ap = {};
		int size = sizeof(struct iwl_tof_range_req_ap_entry);
		u16 burst_period;
		u8 *mac = ap.bssid;
		unsigned int i;

		if (sscanf(data, "%u %hhd %hhd %hhd"
			   "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx"
			   "%hhd %hhd %hd"
			   "%hhd %hhd %d"
			   "%hhx %hhd %hhd %hhd",
			   &i, &ap.channel_num, &ap.bandwidth,
			   &ap.ctrl_ch_position,
			   mac, mac + 1, mac + 2, mac + 3, mac + 4, mac + 5,
			   &ap.measure_type, &ap.num_of_bursts,
			   &burst_period,
			   &ap.samples_per_burst, &ap.retries_per_sample,
			   &ap.tsf_delta, &ap.location_req, &ap.asap_mode,
			   &ap.enable_dyn_ack, &ap.rssi) != 20) {
			ret = -EINVAL;
			goto out;
		}
		if (i >= IWL_MVM_TOF_MAX_APS) {
			IWL_ERR(mvm, "Invalid AP index %d\n", i);
			ret = -EINVAL;
			goto out;
		}

		ap.burst_period = cpu_to_le16(burst_period);

		memcpy(&mvm->tof_data.range_req.ap[i], &ap, size);
		goto out;
	}

	data = iwl_dbgfs_is_match("send_range_request=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0 && value)
			ret = iwl_mvm_tof_range_request_cmd(mvm, vif);
		goto out;
	}

	ret = -EINVAL;
out:
	mutex_unlock(&mvm->mutex);
	return ret ?: count;
}
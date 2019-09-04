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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct iwl_tof_responder_config_cmd {int channel_num; void* asap_mode; void* ftm_resp_ts_avail; void* ftm_per_burst; int /*<<< orphan*/  ctrl_ch_position; void* toa_offset; void* tsf_timer_offset_msecs; int /*<<< orphan*/ * bssid; void* rate; void* bandwidth; void* recv_sta_req_params; void* get_ch_est; void* abort_responder; void* num_of_burst_exp; void* burst_duration; void* min_delta_ftm; void* burst_period; } ;
struct iwl_mvm_vif {struct iwl_mvm* mvm; } ;
struct TYPE_2__ {struct iwl_tof_responder_config_cmd responder_cfg; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_1__ tof_data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_channel {int band; int /*<<< orphan*/  center_freq; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  center_freq1; struct ieee80211_channel* chan; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int EINVAL ; 
 int NL80211_BAND_2GHZ ; 
 int NL80211_BAND_5GHZ ; 
 void* cpu_to_le16 (void*) ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (void*,int) ; 
 char* iwl_dbgfs_is_match (char*,char*) ; 
 int /*<<< orphan*/  iwl_mvm_get_ctrl_pos (struct cfg80211_chan_def*) ; 
 int iwl_mvm_tof_responder_cmd (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int kstrtou32 (char*,int,void**) ; 
 int /*<<< orphan*/  mac_pton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_tof_responder_params_write(struct ieee80211_vif *vif,
						    char *buf,
						    size_t count, loff_t *ppos)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = mvmvif->mvm;
	u32 value;
	int ret = 0;
	char *data;

	mutex_lock(&mvm->mutex);

	data = iwl_dbgfs_is_match("burst_period=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (!ret)
			mvm->tof_data.responder_cfg.burst_period =
							cpu_to_le16(value);
		goto out;
	}

	data = iwl_dbgfs_is_match("min_delta_ftm=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.min_delta_ftm = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("burst_duration=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.burst_duration = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("num_of_burst_exp=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.num_of_burst_exp = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("abort_responder=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.abort_responder = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("get_ch_est=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.get_ch_est = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("recv_sta_req_params=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.recv_sta_req_params = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("channel_num=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.channel_num = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("bandwidth=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.bandwidth = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("rate=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.rate = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("bssid=", buf);
	if (data) {
		u8 *mac = mvm->tof_data.responder_cfg.bssid;

		if (!mac_pton(data, mac)) {
			ret = -EINVAL;
			goto out;
		}
	}

	data = iwl_dbgfs_is_match("tsf_timer_offset_msecs=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.tsf_timer_offset_msecs =
							cpu_to_le16(value);
		goto out;
	}

	data = iwl_dbgfs_is_match("toa_offset=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.toa_offset =
							cpu_to_le16(value);
		goto out;
	}

	data = iwl_dbgfs_is_match("center_freq=", buf);
	if (data) {
		struct iwl_tof_responder_config_cmd *cmd =
			&mvm->tof_data.responder_cfg;

		ret = kstrtou32(data, 10, &value);
		if (ret == 0 && value) {
			enum nl80211_band band = (cmd->channel_num <= 14) ?
						   NL80211_BAND_2GHZ :
						   NL80211_BAND_5GHZ;
			struct ieee80211_channel chn = {
				.band = band,
				.center_freq = ieee80211_channel_to_frequency(
					cmd->channel_num, band),
				};
			struct cfg80211_chan_def chandef = {
				.chan =  &chn,
				.center_freq1 =
					ieee80211_channel_to_frequency(value,
								       band),
			};

			cmd->ctrl_ch_position = iwl_mvm_get_ctrl_pos(&chandef);
		}
		goto out;
	}

	data = iwl_dbgfs_is_match("ftm_per_burst=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.ftm_per_burst = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("ftm_resp_ts_avail=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.ftm_resp_ts_avail = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("asap_mode=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0)
			mvm->tof_data.responder_cfg.asap_mode = value;
		goto out;
	}

	data = iwl_dbgfs_is_match("send_responder_cfg=", buf);
	if (data) {
		ret = kstrtou32(data, 10, &value);
		if (ret == 0 && value) {
			ret = iwl_mvm_tof_responder_cmd(mvm, vif);
			goto out;
		}
	}

out:
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}
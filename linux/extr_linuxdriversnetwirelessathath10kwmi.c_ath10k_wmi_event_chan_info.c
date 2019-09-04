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
struct wmi_ch_info_ev_arg {int /*<<< orphan*/  cycle_count; int /*<<< orphan*/  rx_clear_count; int /*<<< orphan*/  noise_floor; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  freq; int /*<<< orphan*/  err_code; } ;
struct survey_info {int noise; int /*<<< orphan*/  filled; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int state; } ;
struct ath10k {int ch_info_can_report_survey; int survey_last_cycle_count; int survey_last_rx_clear_count; int /*<<< orphan*/  data_lock; struct survey_info* survey; TYPE_1__ scan; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct survey_info*) ; 
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
#define  ATH10K_SCAN_ABORTING 131 
#define  ATH10K_SCAN_IDLE 130 
#define  ATH10K_SCAN_RUNNING 129 
#define  ATH10K_SCAN_STARTING 128 
 int /*<<< orphan*/  SURVEY_INFO_NOISE_DBM ; 
 int WMI_CHAN_INFO_FLAG_COMPLETE ; 
 int WMI_CHAN_INFO_FLAG_PRE_COMPLETE ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ath10k_hw_fill_survey_time (struct ath10k*,struct survey_info*,int,int,int,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int ath10k_wmi_pull_ch_info (struct ath10k*,struct sk_buff*,struct wmi_ch_info_ev_arg*) ; 
 int freq_to_idx (struct ath10k*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ath10k_wmi_event_chan_info(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_ch_info_ev_arg arg = {};
	struct survey_info *survey;
	u32 err_code, freq, cmd_flags, noise_floor, rx_clear_count, cycle_count;
	int idx, ret;

	ret = ath10k_wmi_pull_ch_info(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse chan info event: %d\n", ret);
		return;
	}

	err_code = __le32_to_cpu(arg.err_code);
	freq = __le32_to_cpu(arg.freq);
	cmd_flags = __le32_to_cpu(arg.cmd_flags);
	noise_floor = __le32_to_cpu(arg.noise_floor);
	rx_clear_count = __le32_to_cpu(arg.rx_clear_count);
	cycle_count = __le32_to_cpu(arg.cycle_count);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "chan info err_code %d freq %d cmd_flags %d noise_floor %d rx_clear_count %d cycle_count %d\n",
		   err_code, freq, cmd_flags, noise_floor, rx_clear_count,
		   cycle_count);

	spin_lock_bh(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH10K_SCAN_IDLE:
	case ATH10K_SCAN_STARTING:
		ath10k_warn(ar, "received chan info event without a scan request, ignoring\n");
		goto exit;
	case ATH10K_SCAN_RUNNING:
	case ATH10K_SCAN_ABORTING:
		break;
	}

	idx = freq_to_idx(ar, freq);
	if (idx >= ARRAY_SIZE(ar->survey)) {
		ath10k_warn(ar, "chan info: invalid frequency %d (idx %d out of bounds)\n",
			    freq, idx);
		goto exit;
	}

	if (cmd_flags & WMI_CHAN_INFO_FLAG_COMPLETE) {
		if (ar->ch_info_can_report_survey) {
			survey = &ar->survey[idx];
			survey->noise = noise_floor;
			survey->filled = SURVEY_INFO_NOISE_DBM;

			ath10k_hw_fill_survey_time(ar,
						   survey,
						   cycle_count,
						   rx_clear_count,
						   ar->survey_last_cycle_count,
						   ar->survey_last_rx_clear_count);
		}

		ar->ch_info_can_report_survey = false;
	} else {
		ar->ch_info_can_report_survey = true;
	}

	if (!(cmd_flags & WMI_CHAN_INFO_FLAG_PRE_COMPLETE)) {
		ar->survey_last_rx_clear_count = rx_clear_count;
		ar->survey_last_cycle_count = cycle_count;
	}

exit:
	spin_unlock_bh(&ar->data_lock);
}
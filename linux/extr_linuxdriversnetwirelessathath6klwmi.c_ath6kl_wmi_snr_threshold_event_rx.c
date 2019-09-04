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
typedef  void* u8 ;
struct wmi_snr_threshold_params_cmd {int /*<<< orphan*/  poll_time; int /*<<< orphan*/  weight; void* thresh_below1_val; void* thresh_above1_val; } ;
struct wmi_snr_threshold_event {scalar_t__ snr; scalar_t__ range; } ;
struct wmi {struct sq_threshold_params* sq_threshld; } ;
struct sq_threshold_params {scalar_t__* upper_threshold; scalar_t__* lower_threshold; int /*<<< orphan*/  polling_interval; int /*<<< orphan*/  weight; int /*<<< orphan*/  upper_threshold_valid_count; int /*<<< orphan*/  lower_threshold_valid_count; } ;
typedef  scalar_t__ s16 ;
typedef  enum wmi_snr_threshold_val { ____Placeholder_wmi_snr_threshold_val } wmi_snr_threshold_val ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
 int EIO ; 
 size_t SIGNAL_QUALITY_METRICS_SNR ; 
 int WMI_SNR_THRESHOLD1_ABOVE ; 
 int WMI_SNR_THRESHOLD1_BELOW ; 
 int WMI_SNR_THRESHOLD2_ABOVE ; 
 int WMI_SNR_THRESHOLD2_BELOW ; 
 int WMI_SNR_THRESHOLD3_ABOVE ; 
 int WMI_SNR_THRESHOLD3_BELOW ; 
 int WMI_SNR_THRESHOLD4_ABOVE ; 
 int WMI_SNR_THRESHOLD4_BELOW ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 void* ath6kl_wmi_get_lower_threshold (scalar_t__,struct sq_threshold_params*,int /*<<< orphan*/ ) ; 
 void* ath6kl_wmi_get_upper_threshold (scalar_t__,struct sq_threshold_params*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_send_snr_threshold_params (struct wmi*,struct wmi_snr_threshold_params_cmd*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_snr_threshold_event_rx(struct wmi *wmi, u8 *datap,
					     int len)
{
	struct wmi_snr_threshold_event *reply;
	struct sq_threshold_params *sq_thresh;
	struct wmi_snr_threshold_params_cmd cmd;
	enum wmi_snr_threshold_val new_threshold;
	u8 upper_snr_threshold, lower_snr_threshold;
	s16 snr;
	int ret;

	if (len < sizeof(struct wmi_snr_threshold_event))
		return -EINVAL;

	reply = (struct wmi_snr_threshold_event *) datap;

	new_threshold = (enum wmi_snr_threshold_val) reply->range;
	snr = reply->snr;

	sq_thresh = &wmi->sq_threshld[SIGNAL_QUALITY_METRICS_SNR];

	/*
	 * Identify the threshold breached and communicate that to the app.
	 * After that install a new set of thresholds based on the signal
	 * quality reported by the target.
	 */
	if (new_threshold) {
		/* Upper threshold breached */
		if (snr < sq_thresh->upper_threshold[0]) {
			ath6kl_dbg(ATH6KL_DBG_WMI,
				   "spurious upper snr threshold event: %d\n",
				   snr);
		} else if ((snr < sq_thresh->upper_threshold[1]) &&
			   (snr >= sq_thresh->upper_threshold[0])) {
			new_threshold = WMI_SNR_THRESHOLD1_ABOVE;
		} else if ((snr < sq_thresh->upper_threshold[2]) &&
			   (snr >= sq_thresh->upper_threshold[1])) {
			new_threshold = WMI_SNR_THRESHOLD2_ABOVE;
		} else if ((snr < sq_thresh->upper_threshold[3]) &&
			   (snr >= sq_thresh->upper_threshold[2])) {
			new_threshold = WMI_SNR_THRESHOLD3_ABOVE;
		} else if (snr >= sq_thresh->upper_threshold[3]) {
			new_threshold = WMI_SNR_THRESHOLD4_ABOVE;
		}
	} else {
		/* Lower threshold breached */
		if (snr > sq_thresh->lower_threshold[0]) {
			ath6kl_dbg(ATH6KL_DBG_WMI,
				   "spurious lower snr threshold event: %d\n",
				   sq_thresh->lower_threshold[0]);
		} else if ((snr > sq_thresh->lower_threshold[1]) &&
			   (snr <= sq_thresh->lower_threshold[0])) {
			new_threshold = WMI_SNR_THRESHOLD4_BELOW;
		} else if ((snr > sq_thresh->lower_threshold[2]) &&
			   (snr <= sq_thresh->lower_threshold[1])) {
			new_threshold = WMI_SNR_THRESHOLD3_BELOW;
		} else if ((snr > sq_thresh->lower_threshold[3]) &&
			   (snr <= sq_thresh->lower_threshold[2])) {
			new_threshold = WMI_SNR_THRESHOLD2_BELOW;
		} else if (snr <= sq_thresh->lower_threshold[3]) {
			new_threshold = WMI_SNR_THRESHOLD1_BELOW;
		}
	}

	/* Calculate and install the next set of thresholds */
	lower_snr_threshold = ath6kl_wmi_get_lower_threshold(snr, sq_thresh,
				       sq_thresh->lower_threshold_valid_count);
	upper_snr_threshold = ath6kl_wmi_get_upper_threshold(snr, sq_thresh,
				       sq_thresh->upper_threshold_valid_count);

	/* Issue a wmi command to install the thresholds */
	cmd.thresh_above1_val = upper_snr_threshold;
	cmd.thresh_below1_val = lower_snr_threshold;
	cmd.weight = sq_thresh->weight;
	cmd.poll_time = cpu_to_le32(sq_thresh->polling_interval);

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "snr: %d, threshold: %d, lower: %d, upper: %d\n",
		   snr, new_threshold,
		   lower_snr_threshold, upper_snr_threshold);

	ret = ath6kl_wmi_send_snr_threshold_params(wmi, &cmd);
	if (ret) {
		ath6kl_err("unable to configure snr threshold\n");
		return -EIO;
	}

	return 0;
}
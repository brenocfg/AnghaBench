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
struct wmi_dfs_status_ev_arg {scalar_t__ status; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  radar_confirm; } ;
struct ath10k {TYPE_1__ wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_REGULATORY ; 
 scalar_t__ WMI_HW_RADAR_DETECTED ; 
 scalar_t__ WMI_RADAR_DETECTION_FAIL ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_radar_detected (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_pull_dfs_status (struct ath10k*,struct sk_buff*,struct wmi_dfs_status_ev_arg*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath10k_wmi_event_dfs_status_check(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_dfs_status_ev_arg status_arg = {};
	int ret;

	ret = ath10k_wmi_pull_dfs_status(ar, skb, &status_arg);

	if (ret) {
		ath10k_warn(ar, "failed to parse dfs status event: %d\n", ret);
		return;
	}

	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "dfs status event received from fw: %d\n",
		   status_arg.status);

	/* Even in case of radar detection failure we follow the same
	 * behaviour as if radar is detected i.e to switch to a different
	 * channel.
	 */
	if (status_arg.status == WMI_HW_RADAR_DETECTED ||
	    status_arg.status == WMI_RADAR_DETECTION_FAIL)
		ath10k_radar_detected(ar);
	complete(&ar->wmi.radar_confirm);
}
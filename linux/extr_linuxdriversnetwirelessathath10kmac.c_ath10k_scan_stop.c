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
struct TYPE_4__ {int /*<<< orphan*/  scan_id; } ;
struct wmi_stop_scan_arg {int req_id; TYPE_2__ u; int /*<<< orphan*/  req_type; } ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  completed; } ;
struct ath10k {int /*<<< orphan*/  data_lock; TYPE_1__ scan; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_SCAN_ID ; 
 scalar_t__ ATH10K_SCAN_IDLE ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  WMI_SCAN_STOP_ONE ; 
 int /*<<< orphan*/  __ath10k_scan_finish (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int ath10k_wmi_stop_scan (struct ath10k*,struct wmi_stop_scan_arg*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath10k_scan_stop(struct ath10k *ar)
{
	struct wmi_stop_scan_arg arg = {
		.req_id = 1, /* FIXME */
		.req_type = WMI_SCAN_STOP_ONE,
		.u.scan_id = ATH10K_SCAN_ID,
	};
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath10k_wmi_stop_scan(ar, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to stop wmi scan: %d\n", ret);
		goto out;
	}

	ret = wait_for_completion_timeout(&ar->scan.completed, 3 * HZ);
	if (ret == 0) {
		ath10k_warn(ar, "failed to receive scan abortion completion: timed out\n");
		ret = -ETIMEDOUT;
	} else if (ret > 0) {
		ret = 0;
	}

out:
	/* Scan state should be updated upon scan completion but in case
	 * firmware fails to deliver the event (for whatever reason) it is
	 * desired to clean up scan state anyway. Firmware may have just
	 * dropped the scan completion event delivery due to transport pipe
	 * being overflown with data and/or it can recover on its own before
	 * next scan request is submitted.
	 */
	spin_lock_bh(&ar->data_lock);
	if (ar->scan.state != ATH10K_SCAN_IDLE)
		__ath10k_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);

	return ret;
}
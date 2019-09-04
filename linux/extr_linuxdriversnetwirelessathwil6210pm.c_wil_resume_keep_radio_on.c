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
struct wil6210_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  bus_request_kbps_pre_suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_USER_CLKS_RST_PWGD ; 
 int /*<<< orphan*/  RGF_USER_CLKS_CTL_0 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ no_fw_recovery ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil6210_bus_request (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_c (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wil_down (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,int) ; 
 int /*<<< orphan*/  wil_pm_wake_connected_net_queues (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_status_resuming ; 
 int /*<<< orphan*/  wil_status_suspended ; 
 int /*<<< orphan*/  wil_unmask_irq (struct wil6210_priv*) ; 
 int wil_up (struct wil6210_priv*) ; 
 int wmi_resume (struct wil6210_priv*) ; 

__attribute__((used)) static int wil_resume_keep_radio_on(struct wil6210_priv *wil)
{
	int rc = 0;

	/* wil_status_resuming will be cleared when getting
	 * WMI_TRAFFIC_RESUME_EVENTID
	 */
	set_bit(wil_status_resuming, wil->status);
	clear_bit(wil_status_suspended, wil->status);
	wil_c(wil, RGF_USER_CLKS_CTL_0, BIT_USER_CLKS_RST_PWGD);
	wil_unmask_irq(wil);

	wil6210_bus_request(wil, wil->bus_request_kbps_pre_suspend);

	/* Send WMI resume request to the device */
	rc = wmi_resume(wil);
	if (rc) {
		wil_err(wil, "device failed to resume (%d)\n", rc);
		if (no_fw_recovery)
			goto out;
		rc = wil_down(wil);
		if (rc) {
			wil_err(wil, "wil_down failed (%d)\n", rc);
			goto out;
		}
		rc = wil_up(wil);
		if (rc) {
			wil_err(wil, "wil_up failed (%d)\n", rc);
			goto out;
		}
	}

	/* Wake all queues */
	wil_pm_wake_connected_net_queues(wil);

out:
	if (rc)
		set_bit(wil_status_suspended, wil->status);
	return rc;
}
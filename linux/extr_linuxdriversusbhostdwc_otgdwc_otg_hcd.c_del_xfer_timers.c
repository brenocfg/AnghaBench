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
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */

__attribute__((used)) static void del_xfer_timers(dwc_otg_hcd_t * hcd)
{
#ifdef DEBUG
	int i;
	int num_channels = hcd->core_if->core_params->host_channels;
	for (i = 0; i < num_channels; i++) {
		DWC_TIMER_CANCEL(hcd->core_if->hc_xfer_timer[i]);
	}
#endif
}
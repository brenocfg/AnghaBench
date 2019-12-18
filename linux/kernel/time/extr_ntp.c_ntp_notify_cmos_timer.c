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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_GENERIC_CMOS_UPDATE ; 
 int /*<<< orphan*/  CONFIG_RTC_SYSTOHC ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntp_synced () ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_work ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

void ntp_notify_cmos_timer(void)
{
	if (!ntp_synced())
		return;

	if (IS_ENABLED(CONFIG_GENERIC_CMOS_UPDATE) ||
	    IS_ENABLED(CONFIG_RTC_SYSTOHC))
		queue_delayed_work(system_power_efficient_wq, &sync_work, 0);
}
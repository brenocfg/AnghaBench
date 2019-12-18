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
struct timespec64 {int tv_sec; } ;
struct TYPE_2__ {int tz_minuteswest; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RTC_SYSTOHC ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 scalar_t__ persistent_clock_is_local ; 
 int rtc_set_ntp_time (struct timespec64,unsigned long*) ; 
 int /*<<< orphan*/  sched_sync_hw_clock (struct timespec64,unsigned long,int) ; 
 TYPE_1__ sys_tz ; 

__attribute__((used)) static void sync_rtc_clock(void)
{
	unsigned long target_nsec;
	struct timespec64 adjust, now;
	int rc;

	if (!IS_ENABLED(CONFIG_RTC_SYSTOHC))
		return;

	ktime_get_real_ts64(&now);

	adjust = now;
	if (persistent_clock_is_local)
		adjust.tv_sec -= (sys_tz.tz_minuteswest * 60);

	/*
	 * The current RTC in use will provide the target_nsec it wants to be
	 * called at, and does rtc_tv_nsec_ok internally.
	 */
	rc = rtc_set_ntp_time(adjust, &target_nsec);
	if (rc == -ENODEV)
		return;

	sched_sync_hw_clock(now, target_nsec, rc);
}
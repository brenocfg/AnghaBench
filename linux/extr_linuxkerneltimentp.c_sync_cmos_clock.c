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
 int /*<<< orphan*/  CONFIG_GENERIC_CMOS_UPDATE ; 
 int ENODEV ; 
 int EPROTO ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 scalar_t__ persistent_clock_is_local ; 
 scalar_t__ rtc_tv_nsec_ok (int,struct timespec64*,struct timespec64*) ; 
 int /*<<< orphan*/  sched_sync_hw_clock (struct timespec64,long,int) ; 
 TYPE_1__ sys_tz ; 
 int update_persistent_clock64 (struct timespec64) ; 

__attribute__((used)) static bool sync_cmos_clock(void)
{
	static bool no_cmos;
	struct timespec64 now;
	struct timespec64 adjust;
	int rc = -EPROTO;
	long target_nsec = NSEC_PER_SEC / 2;

	if (!IS_ENABLED(CONFIG_GENERIC_CMOS_UPDATE))
		return false;

	if (no_cmos)
		return false;

	/*
	 * Historically update_persistent_clock64() has followed x86
	 * semantics, which match the MC146818A/etc RTC. This RTC will store
	 * 'adjust' and then in .5s it will advance once second.
	 *
	 * Architectures are strongly encouraged to use rtclib and not
	 * implement this legacy API.
	 */
	ktime_get_real_ts64(&now);
	if (rtc_tv_nsec_ok(-1 * target_nsec, &adjust, &now)) {
		if (persistent_clock_is_local)
			adjust.tv_sec -= (sys_tz.tz_minuteswest * 60);
		rc = update_persistent_clock64(adjust);
		/*
		 * The machine does not support update_persistent_clock64 even
		 * though it defines CONFIG_GENERIC_CMOS_UPDATE.
		 */
		if (rc == -ENODEV) {
			no_cmos = true;
			return false;
		}
	}

	sched_sync_hw_clock(now, target_nsec, rc);
	return true;
}
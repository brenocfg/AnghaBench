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
struct timezone {int tz_minuteswest; } ;
struct timespec64 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int do_settimeofday64 (struct timespec64 const*) ; 
 int security_settime64 (struct timespec64 const*,struct timezone const*) ; 
 struct timezone sys_tz ; 
 int /*<<< orphan*/  timekeeping_warp_clock () ; 
 int /*<<< orphan*/  timespec64_valid_settod (struct timespec64 const*) ; 
 int /*<<< orphan*/  update_vsyscall_tz () ; 

int do_sys_settimeofday64(const struct timespec64 *tv, const struct timezone *tz)
{
	static int firsttime = 1;
	int error = 0;

	if (tv && !timespec64_valid_settod(tv))
		return -EINVAL;

	error = security_settime64(tv, tz);
	if (error)
		return error;

	if (tz) {
		/* Verify we're witin the +-15 hrs range */
		if (tz->tz_minuteswest > 15*60 || tz->tz_minuteswest < -15*60)
			return -EINVAL;

		sys_tz = *tz;
		update_vsyscall_tz();
		if (firsttime) {
			firsttime = 0;
			if (!tv)
				timekeeping_warp_clock();
		}
	}
	if (tv)
		return do_settimeofday64(tv);
	return 0;
}
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
typedef  long time64_t ;
struct timespec64 {long tv_sec; long tv_nsec; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 struct timespec64 timespec64_add_safe (struct timespec64,struct timespec64) ; 
 int /*<<< orphan*/  timespec64_valid (struct timespec64*) ; 

int poll_select_set_timeout(struct timespec64 *to, time64_t sec, long nsec)
{
	struct timespec64 ts = {.tv_sec = sec, .tv_nsec = nsec};

	if (!timespec64_valid(&ts))
		return -EINVAL;

	/* Optimize for the zero timeout value here */
	if (!sec && !nsec) {
		to->tv_sec = to->tv_nsec = 0;
	} else {
		ktime_get_ts64(to);
		*to = timespec64_add_safe(*to, ts);
	}
	return 0;
}
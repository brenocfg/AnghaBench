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
struct timespec64 {int dummy; } ;
typedef  int clockid_t ;

/* Variables and functions */
#define  CLOCK_BOOTTIME 130 
#define  CLOCK_MONOTONIC 129 
#define  CLOCK_REALTIME 128 
 int EINVAL ; 
 int /*<<< orphan*/  ktime_get_boottime_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 

int do_clock_gettime(clockid_t which_clock, struct timespec64 *tp)
{
	switch (which_clock) {
	case CLOCK_REALTIME:
		ktime_get_real_ts64(tp);
		break;
	case CLOCK_MONOTONIC:
		ktime_get_ts64(tp);
		break;
	case CLOCK_BOOTTIME:
		ktime_get_boottime_ts64(tp);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
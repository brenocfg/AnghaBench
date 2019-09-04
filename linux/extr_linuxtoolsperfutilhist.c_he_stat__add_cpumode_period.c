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
typedef  int /*<<< orphan*/  u64 ;
struct he_stat {int /*<<< orphan*/  period_guest_us; int /*<<< orphan*/  period_guest_sys; int /*<<< orphan*/  period_us; int /*<<< orphan*/  period_sys; } ;

/* Variables and functions */
#define  PERF_RECORD_MISC_GUEST_KERNEL 131 
#define  PERF_RECORD_MISC_GUEST_USER 130 
#define  PERF_RECORD_MISC_KERNEL 129 
#define  PERF_RECORD_MISC_USER 128 

__attribute__((used)) static void he_stat__add_cpumode_period(struct he_stat *he_stat,
					unsigned int cpumode, u64 period)
{
	switch (cpumode) {
	case PERF_RECORD_MISC_KERNEL:
		he_stat->period_sys += period;
		break;
	case PERF_RECORD_MISC_USER:
		he_stat->period_us += period;
		break;
	case PERF_RECORD_MISC_GUEST_KERNEL:
		he_stat->period_guest_sys += period;
		break;
	case PERF_RECORD_MISC_GUEST_USER:
		he_stat->period_guest_us += period;
		break;
	default:
		break;
	}
}
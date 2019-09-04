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
struct perf_event {TYPE_1__* pmu; int /*<<< orphan*/ * clock; } ;
typedef  int clockid_t ;
struct TYPE_2__ {int capabilities; } ;

/* Variables and functions */
#define  CLOCK_BOOTTIME 132 
#define  CLOCK_MONOTONIC 131 
#define  CLOCK_MONOTONIC_RAW 130 
#define  CLOCK_REALTIME 129 
#define  CLOCK_TAI 128 
 int EINVAL ; 
 int PERF_PMU_CAP_NO_NMI ; 
 int /*<<< orphan*/  ktime_get_boot_ns ; 
 int /*<<< orphan*/  ktime_get_mono_fast_ns ; 
 int /*<<< orphan*/  ktime_get_raw_fast_ns ; 
 int /*<<< orphan*/  ktime_get_real_ns ; 
 int /*<<< orphan*/  ktime_get_tai_ns ; 

__attribute__((used)) static int perf_event_set_clock(struct perf_event *event, clockid_t clk_id)
{
	bool nmi_safe = false;

	switch (clk_id) {
	case CLOCK_MONOTONIC:
		event->clock = &ktime_get_mono_fast_ns;
		nmi_safe = true;
		break;

	case CLOCK_MONOTONIC_RAW:
		event->clock = &ktime_get_raw_fast_ns;
		nmi_safe = true;
		break;

	case CLOCK_REALTIME:
		event->clock = &ktime_get_real_ns;
		break;

	case CLOCK_BOOTTIME:
		event->clock = &ktime_get_boot_ns;
		break;

	case CLOCK_TAI:
		event->clock = &ktime_get_tai_ns;
		break;

	default:
		return -EINVAL;
	}

	if (!nmi_safe && !(event->pmu->capabilities & PERF_PMU_CAP_NO_NMI))
		return -EINVAL;

	return 0;
}
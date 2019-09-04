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
struct perf_event_attr {int wakeup_events; int /*<<< orphan*/  config; int /*<<< orphan*/  type; int /*<<< orphan*/  sample_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  PERF_COUNT_SW_BPF_OUTPUT ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int /*<<< orphan*/  PERF_SAMPLE_RAW ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bpf_map_update_elem (int,int*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* pmu_fds ; 
 scalar_t__ sys_perf_event_open (struct perf_event_attr*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_bpf_perf_event(int map_fd, int num)
{
	struct perf_event_attr attr = {
		.sample_type = PERF_SAMPLE_RAW,
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_BPF_OUTPUT,
		.wakeup_events = 1, /* get an fd notification for every event */
	};
	int i;

	for (i = 0; i < num; i++) {
		int key = i;

		pmu_fds[i] = sys_perf_event_open(&attr, -1/*pid*/, i/*cpu*/,
						 -1/*group_fd*/, 0);

		assert(pmu_fds[i] >= 0);
		assert(bpf_map_update_elem(map_fd, &key,
					   &pmu_fds[i], BPF_ANY) == 0);
		ioctl(pmu_fds[i], PERF_EVENT_IOC_ENABLE, 0);
	}
}
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
struct perf_event_attr {int sample_type; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  PERF_COUNT_SW_BPF_OUTPUT ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int PERF_SAMPLE_RAW ; 
 int PERF_SAMPLE_TIME ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 scalar_t__ bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,int,int) ; 
 int sys_perf_event_open (struct perf_event_attr*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_perf_event_open(int map_fd, int key, int cpu)
{
	struct perf_event_attr attr = {
		.sample_type = PERF_SAMPLE_RAW | PERF_SAMPLE_TIME,
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_BPF_OUTPUT,
	};
	int pmu_fd;

	pmu_fd = sys_perf_event_open(&attr, -1, cpu, -1, 0);
	if (pmu_fd < 0) {
		p_err("failed to open perf event %d for CPU %d", key, cpu);
		return -1;
	}

	if (bpf_map_update_elem(map_fd, &key, &pmu_fd, BPF_ANY)) {
		p_err("failed to update map for event %d for CPU %d", key, cpu);
		goto err_close;
	}
	if (ioctl(pmu_fd, PERF_EVENT_IOC_ENABLE, 0)) {
		p_err("failed to enable event %d for CPU %d", key, cpu);
		goto err_close;
	}

	return pmu_fd;

err_close:
	close(pmu_fd);
	return -1;
}
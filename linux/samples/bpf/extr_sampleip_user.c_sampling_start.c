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
struct perf_event_attr {int freq; int sample_period; int inherit; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_SW_CPU_CLOCK ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_SET_BPF ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nr_cpus ; 
 int /*<<< orphan*/ * prog_fd ; 
 int /*<<< orphan*/  stderr ; 
 int sys_perf_event_open (struct perf_event_attr*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sampling_start(int *pmu_fd, int freq)
{
	int i;

	struct perf_event_attr pe_sample_attr = {
		.type = PERF_TYPE_SOFTWARE,
		.freq = 1,
		.sample_period = freq,
		.config = PERF_COUNT_SW_CPU_CLOCK,
		.inherit = 1,
	};

	for (i = 0; i < nr_cpus; i++) {
		pmu_fd[i] = sys_perf_event_open(&pe_sample_attr, -1 /* pid */, i,
					    -1 /* group_fd */, 0 /* flags */);
		if (pmu_fd[i] < 0) {
			fprintf(stderr, "ERROR: Initializing perf sampling\n");
			return 1;
		}
		assert(ioctl(pmu_fd[i], PERF_EVENT_IOC_SET_BPF,
			     prog_fd[0]) == 0);
		assert(ioctl(pmu_fd[i], PERF_EVENT_IOC_ENABLE, 0) == 0);
	}

	return 0;
}
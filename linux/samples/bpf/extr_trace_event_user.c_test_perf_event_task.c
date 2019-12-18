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
struct perf_event_attr {int inherit; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EVENT_IOC_DISABLE ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_SET_BPF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ generate_load () ; 
 int /*<<< orphan*/  int_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  print_stacks () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * prog_fd ; 
 int sys_perf_event_open (struct perf_event_attr*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_perf_event_task(struct perf_event_attr *attr)
{
	int pmu_fd, error = 0;

	/* per task perf event, enable inherit so the "dd ..." command can be traced properly.
	 * Enabling inherit will cause bpf_perf_prog_read_time helper failure.
	 */
	attr->inherit = 1;

	/* open task bound event */
	pmu_fd = sys_perf_event_open(attr, 0, -1, -1, 0);
	if (pmu_fd < 0) {
		printf("sys_perf_event_open failed\n");
		int_exit(0);
	}
	assert(ioctl(pmu_fd, PERF_EVENT_IOC_SET_BPF, prog_fd[0]) == 0);
	assert(ioctl(pmu_fd, PERF_EVENT_IOC_ENABLE) == 0);

	if (generate_load() < 0) {
		error = 1;
		goto err;
	}
	print_stacks();
err:
	ioctl(pmu_fd, PERF_EVENT_IOC_DISABLE);
	close(pmu_fd);
	if (error)
		int_exit(0);
}
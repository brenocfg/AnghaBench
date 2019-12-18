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
struct perf_event_attr {scalar_t__ inherit; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EVENT_IOC_DISABLE ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_SET_BPF ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ generate_load () ; 
 int /*<<< orphan*/  int_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  print_stacks () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * prog_fd ; 
 int sys_perf_event_open (struct perf_event_attr*,int,int,int,int /*<<< orphan*/ ) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_perf_event_all_cpu(struct perf_event_attr *attr)
{
	int nr_cpus = sysconf(_SC_NPROCESSORS_CONF);
	int *pmu_fd = malloc(nr_cpus * sizeof(int));
	int i, error = 0;

	/* system wide perf event, no need to inherit */
	attr->inherit = 0;

	/* open perf_event on all cpus */
	for (i = 0; i < nr_cpus; i++) {
		pmu_fd[i] = sys_perf_event_open(attr, -1, i, -1, 0);
		if (pmu_fd[i] < 0) {
			printf("sys_perf_event_open failed\n");
			error = 1;
			goto all_cpu_err;
		}
		assert(ioctl(pmu_fd[i], PERF_EVENT_IOC_SET_BPF, prog_fd[0]) == 0);
		assert(ioctl(pmu_fd[i], PERF_EVENT_IOC_ENABLE) == 0);
	}

	if (generate_load() < 0) {
		error = 1;
		goto all_cpu_err;
	}
	print_stacks();
all_cpu_err:
	for (i--; i >= 0; i--) {
		ioctl(pmu_fd[i], PERF_EVENT_IOC_DISABLE);
		close(pmu_fd[i]);
	}
	free(pmu_fd);
	if (error)
		int_exit(0);
}
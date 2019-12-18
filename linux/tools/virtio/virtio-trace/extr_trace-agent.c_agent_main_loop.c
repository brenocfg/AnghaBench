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
struct agent_info {int cpus; int /*<<< orphan*/  ctl_fd; int /*<<< orphan*/ * rw_ti; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_ctl_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_thread_run (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void agent_main_loop(struct agent_info *s)
{
	int cpu;
	pthread_t rw_thread_per_cpu[MAX_CPUS];

	/* Start all read/write threads */
	for (cpu = 0; cpu < s->cpus; cpu++)
		rw_thread_per_cpu[cpu] = rw_thread_run(s->rw_ti[cpu]);

	rw_ctl_loop(s->ctl_fd);

	/* Finish all read/write threads */
	for (cpu = 0; cpu < s->cpus; cpu++) {
		int ret;

		ret = pthread_join(rw_thread_per_cpu[cpu], NULL);
		if (ret != 0) {
			pr_err("pthread_join() error:%d (cpu %d)\n", ret, cpu);
			exit(EXIT_FAILURE);
		}
	}
}
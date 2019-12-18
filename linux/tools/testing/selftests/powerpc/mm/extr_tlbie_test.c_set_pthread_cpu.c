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
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_setaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void set_pthread_cpu(pthread_t th, int cpu)
{
	cpu_set_t run_cpu_mask;
	struct sched_param param;

	CPU_ZERO(&run_cpu_mask);
	CPU_SET(cpu, &run_cpu_mask);
	pthread_setaffinity_np(th, sizeof(cpu_set_t), &run_cpu_mask);

	param.sched_priority = 1;
	if (0 && sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
		/* haven't reproduced with this setting, it kills random preemption which may be a factor */
		fprintf(stderr, "could not set SCHED_FIFO, run as root?\n");
	}
}
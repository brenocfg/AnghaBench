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
struct smp_call_on_cpu_struct {int (* func ) (void*) ;void* data; unsigned int cpu; int ret; int /*<<< orphan*/  done; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETION_INITIALIZER_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  INIT_WORK_ONSTACK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online (unsigned int) ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  queue_work_on (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_call_on_cpu_callback ; 
 int /*<<< orphan*/  system_wq ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int smp_call_on_cpu(unsigned int cpu, int (*func)(void *), void *par, bool phys)
{
	struct smp_call_on_cpu_struct sscs = {
		.done = COMPLETION_INITIALIZER_ONSTACK(sscs.done),
		.func = func,
		.data = par,
		.cpu  = phys ? cpu : -1,
	};

	INIT_WORK_ONSTACK(&sscs.work, smp_call_on_cpu_callback);

	if (cpu >= nr_cpu_ids || !cpu_online(cpu))
		return -ENXIO;

	queue_work_on(cpu, system_wq, &sscs.work);
	wait_for_completion(&sscs.done);

	return sscs.ret;
}
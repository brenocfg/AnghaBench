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
struct perf_env {int nr_cpus_avail; TYPE_1__* cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  die_id; int /*<<< orphan*/  socket_id; int /*<<< orphan*/  core_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int cpu__max_present_cpu () ; 
 int /*<<< orphan*/  cpu_map__get_core_id (int) ; 
 int /*<<< orphan*/  cpu_map__get_die_id (int) ; 
 int /*<<< orphan*/  cpu_map__get_socket_id (int) ; 

int perf_env__read_cpu_topology_map(struct perf_env *env)
{
	int cpu, nr_cpus;

	if (env->cpu != NULL)
		return 0;

	if (env->nr_cpus_avail == 0)
		env->nr_cpus_avail = cpu__max_present_cpu();

	nr_cpus = env->nr_cpus_avail;
	if (nr_cpus == -1)
		return -EINVAL;

	env->cpu = calloc(nr_cpus, sizeof(env->cpu[0]));
	if (env->cpu == NULL)
		return -ENOMEM;

	for (cpu = 0; cpu < nr_cpus; ++cpu) {
		env->cpu[cpu].core_id	= cpu_map__get_core_id(cpu);
		env->cpu[cpu].socket_id	= cpu_map__get_socket_id(cpu);
		env->cpu[cpu].die_id	= cpu_map__get_die_id(cpu);
	}

	env->nr_cpus_avail = nr_cpus;
	return 0;
}
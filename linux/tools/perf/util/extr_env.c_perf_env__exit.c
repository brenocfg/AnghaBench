#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_env {int nr_numa_nodes; int caches_cnt; int nr_memory_nodes; TYPE_1__* memory_nodes; TYPE_1__* caches; TYPE_1__* numa_nodes; TYPE_1__* cpu; TYPE_1__* pmu_mappings; TYPE_1__* sibling_threads; TYPE_1__* sibling_cores; TYPE_1__* cmdline_argv; TYPE_1__* cmdline; TYPE_1__* cpuid; TYPE_1__* cpu_desc; TYPE_1__* arch; TYPE_1__* version; TYPE_1__* os_release; TYPE_1__* hostname; } ;
struct TYPE_3__ {struct TYPE_3__* set; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_cache_level__free (TYPE_1__*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_env__purge_bpf (struct perf_env*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__**) ; 

void perf_env__exit(struct perf_env *env)
{
	int i;

	perf_env__purge_bpf(env);
	zfree(&env->hostname);
	zfree(&env->os_release);
	zfree(&env->version);
	zfree(&env->arch);
	zfree(&env->cpu_desc);
	zfree(&env->cpuid);
	zfree(&env->cmdline);
	zfree(&env->cmdline_argv);
	zfree(&env->sibling_cores);
	zfree(&env->sibling_threads);
	zfree(&env->pmu_mappings);
	zfree(&env->cpu);

	for (i = 0; i < env->nr_numa_nodes; i++)
		perf_cpu_map__put(env->numa_nodes[i].map);
	zfree(&env->numa_nodes);

	for (i = 0; i < env->caches_cnt; i++)
		cpu_cache_level__free(&env->caches[i]);
	zfree(&env->caches);

	for (i = 0; i < env->nr_memory_nodes; i++)
		zfree(&env->memory_nodes[i].set);
	zfree(&env->memory_nodes);
}
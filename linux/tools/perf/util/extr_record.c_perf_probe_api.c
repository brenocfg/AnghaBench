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
struct perf_cpu_map {int* map; } ;
typedef  int /*<<< orphan*/  setup_probe_fn_t ;

/* Variables and functions */
 int EAGAIN ; 
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int perf_do_probe_api (int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static bool perf_probe_api(setup_probe_fn_t fn)
{
	const char *try[] = {"cycles:u", "instructions:u", "cpu-clock:u", NULL};
	struct perf_cpu_map *cpus;
	int cpu, ret, i = 0;

	cpus = perf_cpu_map__new(NULL);
	if (!cpus)
		return false;
	cpu = cpus->map[0];
	perf_cpu_map__put(cpus);

	do {
		ret = perf_do_probe_api(fn, cpu, try[i++]);
		if (!ret)
			return true;
	} while (ret == -EAGAIN && try[i]);

	return false;
}
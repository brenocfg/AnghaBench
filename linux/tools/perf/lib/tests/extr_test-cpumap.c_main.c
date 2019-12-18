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
struct perf_cpu_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __T_OK ; 
 int /*<<< orphan*/  __T_START ; 
 int /*<<< orphan*/  libperf_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libperf_print ; 
 struct perf_cpu_map* perf_cpu_map__dummy_new () ; 
 int /*<<< orphan*/  perf_cpu_map__get (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 

int main(int argc, char **argv)
{
	struct perf_cpu_map *cpus;

	__T_START;

	libperf_init(libperf_print);

	cpus = perf_cpu_map__dummy_new();
	if (!cpus)
		return -1;

	perf_cpu_map__get(cpus);
	perf_cpu_map__put(cpus);
	perf_cpu_map__put(cpus);

	__T_OK;
	return 0;
}
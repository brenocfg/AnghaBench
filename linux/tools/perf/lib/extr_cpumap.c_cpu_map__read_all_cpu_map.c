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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct perf_cpu_map* cpu_map__default_new () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 struct perf_cpu_map* perf_cpu_map__read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct perf_cpu_map *cpu_map__read_all_cpu_map(void)
{
	struct perf_cpu_map *cpus = NULL;
	FILE *onlnf;

	onlnf = fopen("/sys/devices/system/cpu/online", "r");
	if (!onlnf)
		return cpu_map__default_new();

	cpus = perf_cpu_map__read(onlnf);
	fclose(onlnf);
	return cpus;
}
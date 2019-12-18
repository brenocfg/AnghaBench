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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
union perf_event {TYPE_1__ cpu_map; } ;
struct perf_cpu_map {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ cpu_map__fprintf (struct perf_cpu_map*,int /*<<< orphan*/ *) ; 
 struct perf_cpu_map* cpu_map__new_data (int /*<<< orphan*/ *) ; 
 size_t fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 

size_t perf_event__fprintf_cpu_map(union perf_event *event, FILE *fp)
{
	struct perf_cpu_map *cpus = cpu_map__new_data(&event->cpu_map.data);
	size_t ret;

	ret = fprintf(fp, ": ");

	if (cpus)
		ret += cpu_map__fprintf(cpus, fp);
	else
		ret += fprintf(fp, "failed to get cpumap from event\n");

	perf_cpu_map__put(cpus);
	return ret;
}
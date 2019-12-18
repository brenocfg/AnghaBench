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
struct TYPE_2__ {struct perf_cpu_map* color_cpus; int /*<<< orphan*/  color_cpus_str; } ;
struct perf_sched {TYPE_1__ map; } ;
struct perf_cpu_map {int dummy; } ;

/* Variables and functions */
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_color_cpus(struct perf_sched *sched)
{
	struct perf_cpu_map *map;

	if (!sched->map.color_cpus_str)
		return 0;

	map = perf_cpu_map__new(sched->map.color_cpus_str);
	if (!map) {
		pr_err("failed to get thread map from %s\n", sched->map.color_cpus_str);
		return -1;
	}

	sched->map.color_cpus = map;
	return 0;
}
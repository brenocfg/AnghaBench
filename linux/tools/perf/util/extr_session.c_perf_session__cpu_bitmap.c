#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nr_cpus_online; } ;
struct TYPE_6__ {TYPE_1__ env; } ;
struct perf_session {TYPE_2__ header; } ;
struct perf_cpu_map {int nr; int* map; } ;
struct TYPE_7__ {int sample_type; } ;
struct TYPE_8__ {TYPE_3__ attr; } ;
struct evsel {TYPE_4__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NR_CPUS ; 
 int PERF_SAMPLE_CPU ; 
 int PERF_TYPE_MAX ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct perf_cpu_map* perf_cpu_map__new (char const*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 struct evsel* perf_session__find_first_evtype (struct perf_session*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

int perf_session__cpu_bitmap(struct perf_session *session,
			     const char *cpu_list, unsigned long *cpu_bitmap)
{
	int i, err = -1;
	struct perf_cpu_map *map;
	int nr_cpus = min(session->header.env.nr_cpus_online, MAX_NR_CPUS);

	for (i = 0; i < PERF_TYPE_MAX; ++i) {
		struct evsel *evsel;

		evsel = perf_session__find_first_evtype(session, i);
		if (!evsel)
			continue;

		if (!(evsel->core.attr.sample_type & PERF_SAMPLE_CPU)) {
			pr_err("File does not contain CPU events. "
			       "Remove -C option to proceed.\n");
			return -1;
		}
	}

	map = perf_cpu_map__new(cpu_list);
	if (map == NULL) {
		pr_err("Invalid cpu_list\n");
		return -1;
	}

	for (i = 0; i < map->nr; i++) {
		int cpu = map->map[i];

		if (cpu >= nr_cpus) {
			pr_err("Requested CPU %d too large. "
			       "Consider raising MAX_NR_CPUS\n", cpu);
			goto out_delete_map;
		}

		set_bit(cpu, cpu_bitmap);
	}

	err = 0;

out_delete_map:
	perf_cpu_map__put(map);
	return err;
}
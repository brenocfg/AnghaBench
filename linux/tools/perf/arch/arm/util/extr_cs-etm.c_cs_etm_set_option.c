#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct perf_cpu_map {int dummy; } ;
struct evsel {TYPE_2__* evlist; } ;
struct auxtrace_record {int dummy; } ;
struct TYPE_3__ {struct perf_cpu_map* cpus; } ;
struct TYPE_4__ {TYPE_1__ core; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETM_OPT_CTXTID ; 
 int ETM_OPT_TS ; 
 int cpu__max_cpu () ; 
 int /*<<< orphan*/  cpu_map__has (struct perf_cpu_map*,int) ; 
 int cs_etm_set_context_id (struct auxtrace_record*,struct evsel*,int) ; 
 int cs_etm_set_timestamp (struct auxtrace_record*,struct evsel*,int) ; 
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 

__attribute__((used)) static int cs_etm_set_option(struct auxtrace_record *itr,
			     struct evsel *evsel, u32 option)
{
	int i, err = -EINVAL;
	struct perf_cpu_map *event_cpus = evsel->evlist->core.cpus;
	struct perf_cpu_map *online_cpus = perf_cpu_map__new(NULL);

	/* Set option of each CPU we have */
	for (i = 0; i < cpu__max_cpu(); i++) {
		if (!cpu_map__has(event_cpus, i) ||
		    !cpu_map__has(online_cpus, i))
			continue;

		if (option & ETM_OPT_CTXTID) {
			err = cs_etm_set_context_id(itr, evsel, i);
			if (err)
				goto out;
		}
		if (option & ETM_OPT_TS) {
			err = cs_etm_set_timestamp(itr, evsel, i);
			if (err)
				goto out;
		}
		if (option & ~(ETM_OPT_CTXTID | ETM_OPT_TS))
			/* Nothing else is currently supported */
			goto out;
	}

	err = 0;
out:
	perf_cpu_map__put(online_cpus);
	return err;
}
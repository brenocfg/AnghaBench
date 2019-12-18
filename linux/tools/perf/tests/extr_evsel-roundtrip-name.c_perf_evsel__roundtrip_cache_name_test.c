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
struct evsel {int idx; } ;
struct evlist {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ENOMEM ; 
 int PERF_COUNT_HW_CACHE_MAX ; 
 int PERF_COUNT_HW_CACHE_OP_MAX ; 
 int PERF_COUNT_HW_CACHE_RESULT_MAX ; 
 int /*<<< orphan*/  __perf_evsel__hw_cache_type_op_res_name (int,int,int,char*,int) ; 
 int /*<<< orphan*/  evlist__delete (struct evlist*) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 struct evlist* evlist__new () ; 
 int parse_events (struct evlist*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evsel__is_cache_op_valid (int,int) ; 
 int /*<<< orphan*/  perf_evsel__name (struct evsel*) ; 
 struct evsel* perf_evsel__next (struct evsel*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int perf_evsel__roundtrip_cache_name_test(void)
{
	char name[128];
	int type, op, err = 0, ret = 0, i, idx;
	struct evsel *evsel;
	struct evlist *evlist = evlist__new();

        if (evlist == NULL)
                return -ENOMEM;

	for (type = 0; type < PERF_COUNT_HW_CACHE_MAX; type++) {
		for (op = 0; op < PERF_COUNT_HW_CACHE_OP_MAX; op++) {
			/* skip invalid cache type */
			if (!perf_evsel__is_cache_op_valid(type, op))
				continue;

			for (i = 0; i < PERF_COUNT_HW_CACHE_RESULT_MAX; i++) {
				__perf_evsel__hw_cache_type_op_res_name(type, op, i,
									name, sizeof(name));
				err = parse_events(evlist, name, NULL);
				if (err)
					ret = err;
			}
		}
	}

	idx = 0;
	evsel = evlist__first(evlist);

	for (type = 0; type < PERF_COUNT_HW_CACHE_MAX; type++) {
		for (op = 0; op < PERF_COUNT_HW_CACHE_OP_MAX; op++) {
			/* skip invalid cache type */
			if (!perf_evsel__is_cache_op_valid(type, op))
				continue;

			for (i = 0; i < PERF_COUNT_HW_CACHE_RESULT_MAX; i++) {
				__perf_evsel__hw_cache_type_op_res_name(type, op, i,
									name, sizeof(name));
				if (evsel->idx != idx)
					continue;

				++idx;

				if (strcmp(perf_evsel__name(evsel), name)) {
					pr_debug("%s != %s\n", perf_evsel__name(evsel), name);
					ret = -1;
				}

				evsel = perf_evsel__next(evsel);
			}
		}
	}

	evlist__delete(evlist);
	return ret;
}
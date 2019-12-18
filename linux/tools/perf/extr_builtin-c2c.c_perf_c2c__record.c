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
struct option {int dummy; } ;
struct TYPE_2__ {int record; int /*<<< orphan*/  name; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 struct option OPT_BOOLEAN (char,char*,int*,char*) ; 
 struct option OPT_CALLBACK (char,char*,int*,char*,char*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_PARENT (int /*<<< orphan*/ ) ; 
 struct option OPT_UINTEGER (char,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_UNKNOWN ; 
 size_t PERF_MEM_EVENTS__LOAD ; 
 int PERF_MEM_EVENTS__MAX ; 
 size_t PERF_MEM_EVENTS__STORE ; 
 int /*<<< orphan*/  c2c_options ; 
 char** calloc (int,int) ; 
 int cmd_record (int,char const**) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int parse_options (int,char const**,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_record_events ; 
 TYPE_1__* perf_mem_events ; 
 scalar_t__ perf_mem_events__init () ; 
 int /*<<< orphan*/  perf_mem_events__loads_ldlat ; 
 char* perf_mem_events__name (int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  record_mem_usage ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int perf_c2c__record(int argc, const char **argv)
{
	int rec_argc, i = 0, j;
	const char **rec_argv;
	int ret;
	bool all_user = false, all_kernel = false;
	bool event_set = false;
	struct option options[] = {
	OPT_CALLBACK('e', "event", &event_set, "event",
		     "event selector. Use 'perf mem record -e list' to list available events",
		     parse_record_events),
	OPT_BOOLEAN('u', "all-user", &all_user, "collect only user level data"),
	OPT_BOOLEAN('k', "all-kernel", &all_kernel, "collect only kernel level data"),
	OPT_UINTEGER('l', "ldlat", &perf_mem_events__loads_ldlat, "setup mem-loads latency"),
	OPT_PARENT(c2c_options),
	OPT_END()
	};

	if (perf_mem_events__init()) {
		pr_err("failed: memory events not supported\n");
		return -1;
	}

	argc = parse_options(argc, argv, options, record_mem_usage,
			     PARSE_OPT_KEEP_UNKNOWN);

	rec_argc = argc + 11; /* max number of arguments */
	rec_argv = calloc(rec_argc + 1, sizeof(char *));
	if (!rec_argv)
		return -1;

	rec_argv[i++] = "record";

	if (!event_set) {
		perf_mem_events[PERF_MEM_EVENTS__LOAD].record  = true;
		perf_mem_events[PERF_MEM_EVENTS__STORE].record = true;
	}

	if (perf_mem_events[PERF_MEM_EVENTS__LOAD].record)
		rec_argv[i++] = "-W";

	rec_argv[i++] = "-d";
	rec_argv[i++] = "--phys-data";
	rec_argv[i++] = "--sample-cpu";

	for (j = 0; j < PERF_MEM_EVENTS__MAX; j++) {
		if (!perf_mem_events[j].record)
			continue;

		if (!perf_mem_events[j].supported) {
			pr_err("failed: event '%s' not supported\n",
			       perf_mem_events[j].name);
			free(rec_argv);
			return -1;
		}

		rec_argv[i++] = "-e";
		rec_argv[i++] = perf_mem_events__name(j);
	};

	if (all_user)
		rec_argv[i++] = "--all-user";

	if (all_kernel)
		rec_argv[i++] = "--all-kernel";

	for (j = 0; j < argc; j++, i++)
		rec_argv[i] = argv[j];

	if (verbose > 0) {
		pr_debug("calling: ");

		j = 0;

		while (rec_argv[j]) {
			pr_debug("%s ", rec_argv[j]);
			j++;
		}
		pr_debug("\n");
	}

	ret = cmd_record(i, rec_argv);
	free(rec_argv);
	return ret;
}
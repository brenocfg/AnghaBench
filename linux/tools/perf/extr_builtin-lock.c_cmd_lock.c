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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (scalar_t__) ; 
 unsigned int LOCKHASH_SIZE ; 
 struct option const OPT_BOOLEAN (char,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_END () ; 
 struct option const OPT_INCR (char,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_PARENT (struct option const*) ; 
 struct option const OPT_STRING (char,char*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 int __cmd_record (int,char const**) ; 
 int __cmd_report (int) ; 
 int cmd_script (int,char const**) ; 
 int /*<<< orphan*/  dump_trace ; 
 int /*<<< orphan*/  force ; 
 int /*<<< orphan*/  info_map ; 
 int /*<<< orphan*/  info_threads ; 
 int /*<<< orphan*/  input_name ; 
 scalar_t__ lockhash_table ; 
 int parse_options (int,char const**,struct option const*,char const* const*,int /*<<< orphan*/ ) ; 
 int parse_options_subcommand (int,char const**,struct option const*,char const* const*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_lock_ops ; 
 int /*<<< orphan*/  sort_key ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/ * trace_handler ; 
 int /*<<< orphan*/  usage_with_options (char const**,struct option const*) ; 
 int /*<<< orphan*/  verbose ; 

int cmd_lock(int argc, const char **argv)
{
	const struct option lock_options[] = {
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_INCR('v', "verbose", &verbose, "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('D', "dump-raw-trace", &dump_trace, "dump raw trace in ASCII"),
	OPT_BOOLEAN('f', "force", &force, "don't complain, do it"),
	OPT_END()
	};

	const struct option info_options[] = {
	OPT_BOOLEAN('t', "threads", &info_threads,
		    "dump thread list in perf.data"),
	OPT_BOOLEAN('m', "map", &info_map,
		    "map of lock instances (address:name table)"),
	OPT_PARENT(lock_options)
	};

	const struct option report_options[] = {
	OPT_STRING('k', "key", &sort_key, "acquired",
		    "key for sorting (acquired / contended / avg_wait / wait_total / wait_max / wait_min)"),
	/* TODO: type */
	OPT_PARENT(lock_options)
	};

	const char * const info_usage[] = {
		"perf lock info [<options>]",
		NULL
	};
	const char *const lock_subcommands[] = { "record", "report", "script",
						 "info", NULL };
	const char *lock_usage[] = {
		NULL,
		NULL
	};
	const char * const report_usage[] = {
		"perf lock report [<options>]",
		NULL
	};
	unsigned int i;
	int rc = 0;

	for (i = 0; i < LOCKHASH_SIZE; i++)
		INIT_LIST_HEAD(lockhash_table + i);

	argc = parse_options_subcommand(argc, argv, lock_options, lock_subcommands,
					lock_usage, PARSE_OPT_STOP_AT_NON_OPTION);
	if (!argc)
		usage_with_options(lock_usage, lock_options);

	if (!strncmp(argv[0], "rec", 3)) {
		return __cmd_record(argc, argv);
	} else if (!strncmp(argv[0], "report", 6)) {
		trace_handler = &report_lock_ops;
		if (argc) {
			argc = parse_options(argc, argv,
					     report_options, report_usage, 0);
			if (argc)
				usage_with_options(report_usage, report_options);
		}
		rc = __cmd_report(false);
	} else if (!strcmp(argv[0], "script")) {
		/* Aliased to 'perf script' */
		return cmd_script(argc, argv);
	} else if (!strcmp(argv[0], "info")) {
		if (argc) {
			argc = parse_options(argc, argv,
					     info_options, info_usage, 0);
			if (argc)
				usage_with_options(info_usage, info_options);
		}
		/* recycling report_lock_ops */
		trace_handler = &report_lock_ops;
		rc = __cmd_report(true);
	} else {
		usage_with_options(lock_usage, lock_options);
	}

	return rc;
}
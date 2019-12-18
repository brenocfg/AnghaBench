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
struct perf_attr_details {int verbose; int freq; int event_group; int force; int trace_fields; } ;
struct option {int dummy; } ;

/* Variables and functions */
 struct option const OPT_BOOLEAN (float,char*,int*,char*) ; 
 struct option const OPT_END () ; 
 struct option const OPT_STRING (char,char*,int /*<<< orphan*/ *,char*,char*) ; 
 int __cmd_evlist (int /*<<< orphan*/ ,struct perf_attr_details*) ; 
 int /*<<< orphan*/  input_name ; 
 int parse_options (int,char const**,struct option const*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option const*) ; 
 int /*<<< orphan*/  usage_with_options_msg (char const* const*,struct option const*,char*) ; 

int cmd_evlist(int argc, const char **argv)
{
	struct perf_attr_details details = { .verbose = false, };
	const struct option options[] = {
	OPT_STRING('i', "input", &input_name, "file", "Input file name"),
	OPT_BOOLEAN('F', "freq", &details.freq, "Show the sample frequency"),
	OPT_BOOLEAN('v', "verbose", &details.verbose,
		    "Show all event attr details"),
	OPT_BOOLEAN('g', "group", &details.event_group,
		    "Show event group information"),
	OPT_BOOLEAN('f', "force", &details.force, "don't complain, do it"),
	OPT_BOOLEAN(0, "trace-fields", &details.trace_fields, "Show tracepoint fields"),
	OPT_END()
	};
	const char * const evlist_usage[] = {
		"perf evlist [<options>]",
		NULL
	};

	argc = parse_options(argc, argv, options, evlist_usage, 0);
	if (argc)
		usage_with_options(evlist_usage, options);

	if (details.event_group && (details.verbose || details.freq)) {
		usage_with_options_msg(evlist_usage, options,
			"--group option is not compatible with other options\n");
	}

	return __cmd_evlist(input_name, &details);
}
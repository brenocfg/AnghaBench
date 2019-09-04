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
 struct option const OPT_BOOLEAN (char,char*,int*,char*) ; 
 struct option const OPT_END () ; 
 struct option const OPT_INCR (char,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_STRING (char,char*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  input_name ; 
 int parse_options (int,char const**,struct option const*,char const* const*,int /*<<< orphan*/ ) ; 
 int perf_session__list_build_ids (int,int) ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ sysfs__fprintf_build_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose ; 

int cmd_buildid_list(int argc, const char **argv)
{
	bool show_kernel = false;
	bool with_hits = false;
	bool force = false;
	const struct option options[] = {
	OPT_BOOLEAN('H', "with-hits", &with_hits, "Show only DSOs with hits"),
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_BOOLEAN('f', "force", &force, "don't complain, do it"),
	OPT_BOOLEAN('k', "kernel", &show_kernel, "Show current kernel build id"),
	OPT_INCR('v', "verbose", &verbose, "be more verbose"),
	OPT_END()
	};
	const char * const buildid_list_usage[] = {
		"perf buildid-list [<options>]",
		NULL
	};

	argc = parse_options(argc, argv, options, buildid_list_usage, 0);
	setup_pager();

	if (show_kernel)
		return !(sysfs__fprintf_build_id(stdout) > 0);

	return perf_session__list_build_ids(force, with_hits);
}
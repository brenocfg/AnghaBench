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
struct intlist {int dummy; } ;
struct TYPE_2__ {int priv_size; int sort_by_name; int try_vmlinux_path; } ;

/* Variables and functions */
 struct option const OPT_BOOLEAN (float,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_END () ; 
 struct option const OPT_INCR (char,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_STRING (char,char*,char const**,char*,char*) ; 
 int __cmd_test (int,char const**,struct intlist*) ; 
 int /*<<< orphan*/  dont_fork ; 
 int hists__init () ; 
 struct intlist* intlist__new (char const*) ; 
 int parse_options_subcommand (int,char const**,struct option const*,char const* const*,char const**,int /*<<< orphan*/ ) ; 
 int perf_test__list (int,char const**) ; 
 int /*<<< orphan*/  rlimit__bump_memlock () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ symbol__init (int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  verbose ; 

int cmd_test(int argc, const char **argv)
{
	const char *test_usage[] = {
	"perf test [<options>] [{list <test-name-fragment>|[<test-name-fragments>|<test-numbers>]}]",
	NULL,
	};
	const char *skip = NULL;
	const struct option test_options[] = {
	OPT_STRING('s', "skip", &skip, "tests", "tests to skip"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('F', "dont-fork", &dont_fork,
		    "Do not fork for testcase"),
	OPT_END()
	};
	const char * const test_subcommands[] = { "list", NULL };
	struct intlist *skiplist = NULL;
        int ret = hists__init();

        if (ret < 0)
                return ret;

	argc = parse_options_subcommand(argc, argv, test_options, test_subcommands, test_usage, 0);
	if (argc >= 1 && !strcmp(argv[0], "list"))
		return perf_test__list(argc - 1, argv + 1);

	symbol_conf.priv_size = sizeof(int);
	symbol_conf.sort_by_name = true;
	symbol_conf.try_vmlinux_path = true;

	if (symbol__init(NULL) < 0)
		return -1;

	if (skip != NULL)
		skiplist = intlist__new(skip);
	/*
	 * Tests that create BPF maps, for instance, need more than the 64K
	 * default:
	 */
	rlimit__bump_memlock();

	return __cmd_test(argc, argv, skiplist);
}
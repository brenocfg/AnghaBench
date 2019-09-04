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
struct TYPE_2__ {int sort_by_name; int /*<<< orphan*/ * vmlinux_name; int /*<<< orphan*/  try_vmlinux_path; } ;

/* Variables and functions */
 struct option const OPT_END () ; 
 struct option const OPT_INCR (char,char*,int /*<<< orphan*/ *,char*) ; 
 int __cmd_kallsyms (int,char const**) ; 
 int parse_options (int,char const**,struct option const*,char const* const*,int /*<<< orphan*/ ) ; 
 scalar_t__ symbol__init (int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option const*) ; 
 int /*<<< orphan*/  verbose ; 

int cmd_kallsyms(int argc, const char **argv)
{
	const struct option options[] = {
	OPT_INCR('v', "verbose", &verbose, "be more verbose (show counter open errors, etc)"),
	OPT_END()
	};
	const char * const kallsyms_usage[] = {
		"perf kallsyms [<options>] symbol_name",
		NULL
	};

	argc = parse_options(argc, argv, options, kallsyms_usage, 0);
	if (argc < 1)
		usage_with_options(kallsyms_usage, options);

	symbol_conf.sort_by_name = true;
	symbol_conf.try_vmlinux_path = (symbol_conf.vmlinux_name == NULL);
	if (symbol__init(NULL) < 0)
		return -1;

	return __cmd_kallsyms(argc, argv);
}
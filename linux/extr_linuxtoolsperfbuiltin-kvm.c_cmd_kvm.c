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
struct TYPE_2__ {char const* guestmount; char const* default_guest_vmlinux_name; char const* default_guest_kallsyms; char const* default_guest_modules; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct option const OPT_BOOLEAN (int /*<<< orphan*/ ,char*,int*,char*) ; 
 struct option const OPT_END () ; 
 struct option const OPT_INCR (char,char*,int /*<<< orphan*/ *,char*) ; 
 struct option const OPT_STRING (char,char*,char const**,char*,char*) ; 
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 int __cmd_buildid_list (char const*,int,char const**) ; 
 int __cmd_record (char const*,int,char const**) ; 
 int __cmd_report (char const*,int,char const**) ; 
 int cmd_diff (int,char const**) ; 
 int cmd_top (int,char const**) ; 
 char* get_filename_for_perf_kvm () ; 
 int parse_options_subcommand (int,char const**,struct option const*,char const* const*,char const**,int /*<<< orphan*/ ) ; 
 int perf_guest ; 
 int perf_host ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  usage_with_options (char const**,struct option const*) ; 
 int /*<<< orphan*/  verbose ; 

int cmd_kvm(int argc, const char **argv)
{
	const char *file_name = NULL;
	const struct option kvm_options[] = {
		OPT_STRING('i', "input", &file_name, "file",
			   "Input file name"),
		OPT_STRING('o', "output", &file_name, "file",
			   "Output file name"),
		OPT_BOOLEAN(0, "guest", &perf_guest,
			    "Collect guest os data"),
		OPT_BOOLEAN(0, "host", &perf_host,
			    "Collect host os data"),
		OPT_STRING(0, "guestmount", &symbol_conf.guestmount, "directory",
			   "guest mount directory under which every guest os"
			   " instance has a subdir"),
		OPT_STRING(0, "guestvmlinux", &symbol_conf.default_guest_vmlinux_name,
			   "file", "file saving guest os vmlinux"),
		OPT_STRING(0, "guestkallsyms", &symbol_conf.default_guest_kallsyms,
			   "file", "file saving guest os /proc/kallsyms"),
		OPT_STRING(0, "guestmodules", &symbol_conf.default_guest_modules,
			   "file", "file saving guest os /proc/modules"),
		OPT_INCR('v', "verbose", &verbose,
			    "be more verbose (show counter open errors, etc)"),
		OPT_END()
	};

	const char *const kvm_subcommands[] = { "top", "record", "report", "diff",
						"buildid-list", "stat", NULL };
	const char *kvm_usage[] = { NULL, NULL };

	perf_host  = 0;
	perf_guest = 1;

	argc = parse_options_subcommand(argc, argv, kvm_options, kvm_subcommands, kvm_usage,
					PARSE_OPT_STOP_AT_NON_OPTION);
	if (!argc)
		usage_with_options(kvm_usage, kvm_options);

	if (!perf_host)
		perf_guest = 1;

	if (!file_name) {
		file_name = get_filename_for_perf_kvm();

		if (!file_name) {
			pr_err("Failed to allocate memory for filename\n");
			return -ENOMEM;
		}
	}

	if (!strncmp(argv[0], "rec", 3))
		return __cmd_record(file_name, argc, argv);
	else if (!strncmp(argv[0], "rep", 3))
		return __cmd_report(file_name, argc, argv);
	else if (!strncmp(argv[0], "diff", 4))
		return cmd_diff(argc, argv);
	else if (!strncmp(argv[0], "top", 3))
		return cmd_top(argc, argv);
	else if (!strncmp(argv[0], "buildid-list", 12))
		return __cmd_buildid_list(file_name, argc, argv);
#ifdef HAVE_KVM_STAT_SUPPORT
	else if (!strncmp(argv[0], "stat", 4))
		return kvm_cmd_stat(file_name, argc, argv);
#endif
	else
		usage_with_options(kvm_usage, kvm_options);

	return 0;
}
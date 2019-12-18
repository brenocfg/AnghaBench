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
typedef  enum help_format { ____Placeholder_help_format } help_format ;

/* Variables and functions */
#define  HELP_FORMAT_INFO 131 
#define  HELP_FORMAT_MAN 130 
#define  HELP_FORMAT_NONE 129 
#define  HELP_FORMAT_WEB 128 
 struct option OPT_BOOLEAN (char,char*,int*,char*) ; 
 struct option OPT_END () ; 
 struct option OPT_SET_UINT (char,char*,int*,char*,int) ; 
 int /*<<< orphan*/  list_commands (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_common_cmds_help () ; 
 int /*<<< orphan*/  load_command_list (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_cmds ; 
 int /*<<< orphan*/  other_cmds ; 
 int parse_options_subcommand (int,char const**,struct option*,char const* const*,char const**,int /*<<< orphan*/ ) ; 
 int perf_config (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  perf_help_config ; 
 char* perf_more_info_string ; 
 char* perf_usage_string ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int show_html_page (char const*) ; 
 int show_info_page (char const*) ; 
 int show_man_page (char const*) ; 

int cmd_help(int argc, const char **argv)
{
	bool show_all = false;
	enum help_format help_format = HELP_FORMAT_MAN;
	struct option builtin_help_options[] = {
	OPT_BOOLEAN('a', "all", &show_all, "print all available commands"),
	OPT_SET_UINT('m', "man", &help_format, "show man page", HELP_FORMAT_MAN),
	OPT_SET_UINT('w', "web", &help_format, "show manual in web browser",
			HELP_FORMAT_WEB),
	OPT_SET_UINT('i', "info", &help_format, "show info page",
			HELP_FORMAT_INFO),
	OPT_END(),
	};
	const char * const builtin_help_subcommands[] = {
		"buildid-cache", "buildid-list", "diff", "evlist", "help", "list",
		"record", "report", "bench", "stat", "timechart", "top", "annotate",
		"script", "sched", "kallsyms", "kmem", "lock", "kvm", "test", "inject", "mem", "data",
#ifdef HAVE_LIBELF_SUPPORT
		"probe",
#endif
#if defined(HAVE_LIBAUDIT_SUPPORT) || defined(HAVE_SYSCALL_TABLE_SUPPORT)
		"trace",
#endif
	NULL };
	const char *builtin_help_usage[] = {
		"perf help [--all] [--man|--web|--info] [command]",
		NULL
	};
	int rc;

	load_command_list("perf-", &main_cmds, &other_cmds);

	rc = perf_config(perf_help_config, &help_format);
	if (rc)
		return rc;

	argc = parse_options_subcommand(argc, argv, builtin_help_options,
			builtin_help_subcommands, builtin_help_usage, 0);

	if (show_all) {
		printf("\n Usage: %s\n\n", perf_usage_string);
		list_commands("perf commands", &main_cmds, &other_cmds);
		printf(" %s\n\n", perf_more_info_string);
		return 0;
	}

	if (!argv[0]) {
		printf("\n usage: %s\n\n", perf_usage_string);
		list_common_cmds_help();
		printf("\n %s\n\n", perf_more_info_string);
		return 0;
	}

	switch (help_format) {
	case HELP_FORMAT_MAN:
		rc = show_man_page(argv[0]);
		break;
	case HELP_FORMAT_INFO:
		rc = show_info_page(argv[0]);
		break;
	case HELP_FORMAT_WEB:
		rc = show_html_page(argv[0]);
		break;
	case HELP_FORMAT_NONE:
		/* fall-through */
	default:
		rc = -1;
		break;
	}

	return rc;
}
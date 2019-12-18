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
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EXEC_PATH_ENVIRONMENT ; 
 int /*<<< orphan*/  PERF_EXEC_PATH ; 
 int /*<<< orphan*/  PERF_PAGER_ENVIRONMENT ; 
 int /*<<< orphan*/  PREFIX ; 
 int STRERR_BUFSIZE ; 
 int cmd_trace (int,char const**) ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 int /*<<< orphan*/  config_exclusive_filename ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exec_cmd_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* extract_argv0_path (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  handle_internal_command (int,char const**) ; 
 int /*<<< orphan*/  handle_options (char const***,int*,int /*<<< orphan*/ *) ; 
 char* help_unknown_cmd (char const*) ; 
 int /*<<< orphan*/  libperf_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libperf_print ; 
 int /*<<< orphan*/  list_common_cmds_help () ; 
 int /*<<< orphan*/  pager_init (int /*<<< orphan*/ ) ; 
 int perf_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_debug_setup () ; 
 int /*<<< orphan*/  perf_default_config ; 
 char* perf_more_info_string ; 
 char* perf_usage_string ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  pthread__block_sigwinch () ; 
 int /*<<< orphan*/  run_argv (int*,char const***) ; 
 int /*<<< orphan*/  set_buildid_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_path () ; 
 int /*<<< orphan*/  srandom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* str_error_r (scalar_t__,char*,int) ; 
 scalar_t__ strstarts (char const*,char*) ; 
 int /*<<< orphan*/  test_attr__init () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(int argc, const char **argv)
{
	int err;
	const char *cmd;
	char sbuf[STRERR_BUFSIZE];

	/* libsubcmd init */
	exec_cmd_init("perf", PREFIX, PERF_EXEC_PATH, EXEC_PATH_ENVIRONMENT);
	pager_init(PERF_PAGER_ENVIRONMENT);

	libperf_init(libperf_print);

	cmd = extract_argv0_path(argv[0]);
	if (!cmd)
		cmd = "perf-help";

	srandom(time(NULL));

	/* Setting $PERF_CONFIG makes perf read _only_ the given config file. */
	config_exclusive_filename = getenv("PERF_CONFIG");

	err = perf_config(perf_default_config, NULL);
	if (err)
		return err;
	set_buildid_dir(NULL);

	/*
	 * "perf-xxxx" is the same as "perf xxxx", but we obviously:
	 *
	 *  - cannot take flags in between the "perf" and the "xxxx".
	 *  - cannot execute it externally (since it would just do
	 *    the same thing over again)
	 *
	 * So we just directly call the internal command handler. If that one
	 * fails to handle this, then maybe we just run a renamed perf binary
	 * that contains a dash in its name. To handle this scenario, we just
	 * fall through and ignore the "xxxx" part of the command string.
	 */
	if (strstarts(cmd, "perf-")) {
		cmd += 5;
		argv[0] = cmd;
		handle_internal_command(argc, argv);
		/*
		 * If the command is handled, the above function does not
		 * return undo changes and fall through in such a case.
		 */
		cmd -= 5;
		argv[0] = cmd;
	}
	if (strstarts(cmd, "trace")) {
#if defined(HAVE_LIBAUDIT_SUPPORT) || defined(HAVE_SYSCALL_TABLE_SUPPORT)
		setup_path();
		argv[0] = "trace";
		return cmd_trace(argc, argv);
#else
		fprintf(stderr,
			"trace command not available: missing audit-libs devel package at build time.\n");
		goto out;
#endif
	}
	/* Look for flags.. */
	argv++;
	argc--;
	handle_options(&argv, &argc, NULL);
	commit_pager_choice();

	if (argc > 0) {
		if (strstarts(argv[0], "--"))
			argv[0] += 2;
	} else {
		/* The user didn't specify a command; give them help */
		printf("\n usage: %s\n\n", perf_usage_string);
		list_common_cmds_help();
		printf("\n %s\n\n", perf_more_info_string);
		goto out;
	}
	cmd = argv[0];

	test_attr__init();

	/*
	 * We use PATH to find perf commands, but we prepend some higher
	 * precedence paths: the "--exec-path" option, the PERF_EXEC_PATH
	 * environment, and the $(perfexecdir) from the Makefile at build
	 * time.
	 */
	setup_path();
	/*
	 * Block SIGWINCH notifications so that the thread that wants it can
	 * unblock and get syscalls like select interrupted instead of waiting
	 * forever while the signal goes to some other non interested thread.
	 */
	pthread__block_sigwinch();

	perf_debug_setup();

	while (1) {
		static int done_help;

		run_argv(&argc, &argv);

		if (errno != ENOENT)
			break;

		if (!done_help) {
			cmd = argv[0] = help_unknown_cmd(cmd);
			done_help = 1;
		} else
			break;
	}

	fprintf(stderr, "Failed to run command '%s': %s\n",
		cmd, str_error_r(errno, sbuf, sizeof(sbuf)));
out:
	return 1;
}
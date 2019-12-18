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
struct option {char* long_name; } ;
struct cmd_struct {char* cmd; } ;

/* Variables and functions */
 int ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CMD_DEBUGFS_DIR ; 
 int /*<<< orphan*/  CMD_EXEC_PATH ; 
 int /*<<< orphan*/  PERF_HTML_PATH ; 
 void* commands ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_argv_exec_path () ; 
 void* options ; 
 scalar_t__ perf_debug_option (char const*) ; 
 int /*<<< orphan*/  perf_usage_string ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_argv_exec_path (char const*) ; 
 int /*<<< orphan*/  set_buildid_dir (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strstarts (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_path (int /*<<< orphan*/ ) ; 
 char* tracing_path_mount () ; 
 int /*<<< orphan*/  tracing_path_set (char const*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int use_pager ; 
 int version_verbose ; 

__attribute__((used)) static int handle_options(const char ***argv, int *argc, int *envchanged)
{
	int handled = 0;

	while (*argc > 0) {
		const char *cmd = (*argv)[0];
		if (cmd[0] != '-')
			break;

		/*
		 * For legacy reasons, the "version" and "help"
		 * commands can be written with "--" prepended
		 * to make them look like flags.
		 */
		if (!strcmp(cmd, "--help") || !strcmp(cmd, "--version"))
			break;

		/*
		 * Shortcut for '-h' and '-v' options to invoke help
		 * and version command.
		 */
		if (!strcmp(cmd, "-h")) {
			(*argv)[0] = "--help";
			break;
		}

		if (!strcmp(cmd, "-v")) {
			(*argv)[0] = "--version";
			break;
		}

		if (!strcmp(cmd, "-vv")) {
			(*argv)[0] = "version";
			version_verbose = 1;
			break;
		}

		/*
		 * Check remaining flags.
		 */
		if (strstarts(cmd, CMD_EXEC_PATH)) {
			cmd += strlen(CMD_EXEC_PATH);
			if (*cmd == '=')
				set_argv_exec_path(cmd + 1);
			else {
				puts(get_argv_exec_path());
				exit(0);
			}
		} else if (!strcmp(cmd, "--html-path")) {
			puts(system_path(PERF_HTML_PATH));
			exit(0);
		} else if (!strcmp(cmd, "-p") || !strcmp(cmd, "--paginate")) {
			use_pager = 1;
		} else if (!strcmp(cmd, "--no-pager")) {
			use_pager = 0;
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--debugfs-dir")) {
			if (*argc < 2) {
				fprintf(stderr, "No directory given for --debugfs-dir.\n");
				usage(perf_usage_string);
			}
			tracing_path_set((*argv)[1]);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		} else if (!strcmp(cmd, "--buildid-dir")) {
			if (*argc < 2) {
				fprintf(stderr, "No directory given for --buildid-dir.\n");
				usage(perf_usage_string);
			}
			set_buildid_dir((*argv)[1]);
			if (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		} else if (strstarts(cmd, CMD_DEBUGFS_DIR)) {
			tracing_path_set(cmd + strlen(CMD_DEBUGFS_DIR));
			fprintf(stderr, "dir: %s\n", tracing_path_mount());
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--list-cmds")) {
			unsigned int i;

			for (i = 0; i < ARRAY_SIZE(commands); i++) {
				struct cmd_struct *p = commands+i;
				printf("%s ", p->cmd);
			}
			putchar('\n');
			exit(0);
		} else if (!strcmp(cmd, "--list-opts")) {
			unsigned int i;

			for (i = 0; i < ARRAY_SIZE(options)-1; i++) {
				struct option *p = options+i;
				printf("--%s ", p->long_name);
			}
			putchar('\n');
			exit(0);
		} else if (!strcmp(cmd, "--debug")) {
			if (*argc < 2) {
				fprintf(stderr, "No variable specified for --debug.\n");
				usage(perf_usage_string);
			}
			if (perf_debug_option((*argv)[1]))
				usage(perf_usage_string);

			(*argv)++;
			(*argc)--;
		} else {
			fprintf(stderr, "Unknown option: %s\n", cmd);
			usage(perf_usage_string);
		}

		(*argv)++;
		(*argc)--;
		handled++;
	}
	return handled;
}
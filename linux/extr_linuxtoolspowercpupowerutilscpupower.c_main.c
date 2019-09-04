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
struct utsname {char const* machine; } ;
struct stat {int dummy; } ;
struct cmd_struct {char const* cmd; unsigned int (* main ) (int,char const**) ;scalar_t__ needs_root; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct cmd_struct*) ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  PACKAGE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 scalar_t__ base_cpu ; 
 scalar_t__ bitmask_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmask_free (scalar_t__) ; 
 struct cmd_struct* commands ; 
 int /*<<< orphan*/  cpupower_cpu_info ; 
 scalar_t__ cpus_chosen ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_cpu_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  handle_options (int*,char const***) ; 
 int /*<<< orphan*/  print_help () ; 
 int run_as_root ; 
 scalar_t__ sched_getcpu () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 unsigned int stub1 (int,char const**) ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 
 int system (char*) ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 unsigned int uname (struct utsname*) ; 

int main(int argc, const char *argv[])
{
	const char *cmd;
	unsigned int i, ret;
	struct stat statbuf;
	struct utsname uts;
	char pathname[32];

	cpus_chosen = bitmask_alloc(sysconf(_SC_NPROCESSORS_CONF));

	argc--;
	argv += 1;

	handle_options(&argc, &argv);

	cmd = argv[0];

	if (argc < 1) {
		print_help();
		return EXIT_FAILURE;
	}

	setlocale(LC_ALL, "");
	textdomain(PACKAGE);

	/* Turn "perf cmd --help" into "perf help cmd" */
	if (argc > 1 && !strcmp(argv[1], "--help")) {
		argv[1] = argv[0];
		argv[0] = cmd = "help";
	}

	base_cpu = sched_getcpu();
	if (base_cpu < 0) {
		fprintf(stderr, _("No valid cpus found.\n"));
		return EXIT_FAILURE;
	}

	get_cpu_info(&cpupower_cpu_info);
	run_as_root = !geteuid();
	if (run_as_root) {
		ret = uname(&uts);
		sprintf(pathname, "/dev/cpu/%d/msr", base_cpu);
		if (!ret && !strcmp(uts.machine, "x86_64") &&
		    stat(pathname, &statbuf) != 0) {
			if (system("modprobe msr") == -1)
	fprintf(stderr, _("MSR access not available.\n"));
		}
	}

	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		struct cmd_struct *p = commands + i;
		if (strcmp(p->cmd, cmd))
			continue;
		if (!run_as_root && p->needs_root) {
			fprintf(stderr, _("Subcommand %s needs root "
					  "privileges\n"), cmd);
			return EXIT_FAILURE;
		}
		ret = p->main(argc, argv);
		if (cpus_chosen)
			bitmask_free(cpus_chosen);
		return ret;
	}
	print_help();
	return EXIT_FAILURE;
}
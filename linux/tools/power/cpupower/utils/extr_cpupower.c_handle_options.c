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

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 char* _ (char*) ; 
 int be_verbose ; 
 int bitmask_parselist (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmask_setall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_chosen ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_help () ; 
 int /*<<< orphan*/  print_version () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void handle_options(int *argc, const char ***argv)
{
	int ret, x, new_argc = 0;

	if (*argc < 1)
		return;

	for (x = 0;  x < *argc && ((*argv)[x])[0] == '-'; x++) {
		const char *param = (*argv)[x];
		if (!strcmp(param, "-h") || !strcmp(param, "--help")) {
			print_help();
			exit(EXIT_SUCCESS);
		} else if (!strcmp(param, "-c") || !strcmp(param, "--cpu")) {
			if (*argc < 2) {
				print_help();
				exit(EXIT_FAILURE);
			}
			if (!strcmp((*argv)[x+1], "all"))
				bitmask_setall(cpus_chosen);
			else {
				ret = bitmask_parselist(
						(*argv)[x+1], cpus_chosen);
				if (ret < 0) {
					fprintf(stderr, _("Error parsing cpu "
							  "list\n"));
					exit(EXIT_FAILURE);
				}
			}
			x += 1;
			/* Cut out param: cpupower -c 1 info -> cpupower info */
			new_argc += 2;
			continue;
		} else if (!strcmp(param, "-v") ||
			!strcmp(param, "--version")) {
			print_version();
			exit(EXIT_SUCCESS);
#ifdef DEBUG
		} else if (!strcmp(param, "-d") || !strcmp(param, "--debug")) {
			be_verbose = 1;
			new_argc++;
			continue;
#endif
		} else {
			fprintf(stderr, "Unknown option: %s\n", param);
			print_help();
			exit(EXIT_FAILURE);
		}
	}
	*argc -= new_argc;
	*argv += new_argc;
}
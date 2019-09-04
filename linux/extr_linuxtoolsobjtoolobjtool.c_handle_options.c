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
 int /*<<< orphan*/  cmd_usage () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int help ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void handle_options(int *argc, const char ***argv)
{
	while (*argc > 0) {
		const char *cmd = (*argv)[0];

		if (cmd[0] != '-')
			break;

		if (!strcmp(cmd, "--help") || !strcmp(cmd, "-h")) {
			help = true;
			break;
		} else {
			fprintf(stderr, "Unknown option: %s\n", cmd);
			cmd_usage();
		}

		(*argv)++;
		(*argc)--;
	}
}
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
struct cmd_struct {char const* cmd; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct cmd_struct*) ; 
 struct cmd_struct* commands ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_builtin (struct cmd_struct*,int,char const**) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void handle_internal_command(int argc, const char **argv)
{
	const char *cmd = argv[0];
	unsigned int i;

	/* Turn "perf cmd --help" into "perf help cmd" */
	if (argc > 1 && !strcmp(argv[1], "--help")) {
		argv[1] = argv[0];
		argv[0] = cmd = "help";
	}

	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		struct cmd_struct *p = commands+i;
		if (strcmp(p->cmd, cmd))
			continue;
		exit(run_builtin(p, argc, argv));
	}
}
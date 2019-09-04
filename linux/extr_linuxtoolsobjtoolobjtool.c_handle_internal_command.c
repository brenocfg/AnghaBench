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
struct cmd_struct {unsigned int (* fn ) (int,char const**) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct cmd_struct*) ; 
 int /*<<< orphan*/  cmd_usage () ; 
 int /*<<< orphan*/  exit (unsigned int) ; 
 struct cmd_struct* objtool_cmds ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 unsigned int stub1 (int,char const**) ; 

__attribute__((used)) static void handle_internal_command(int argc, const char **argv)
{
	const char *cmd = argv[0];
	unsigned int i, ret;

	for (i = 0; i < ARRAY_SIZE(objtool_cmds); i++) {
		struct cmd_struct *p = objtool_cmds+i;

		if (strcmp(p->name, cmd))
			continue;

		ret = p->fn(argc, argv);

		exit(ret);
	}

	cmd_usage();
}
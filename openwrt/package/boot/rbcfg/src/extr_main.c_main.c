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
struct rbcfg_command {int flags; int (* exec ) (int,char const**) ;int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rbcfg_command*) ; 
 int CMD_FLAG_USES_CFG ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  fixup_rbcfg_envs () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  rbcfg_close () ; 
 struct rbcfg_command* rbcfg_commands ; 
 char* rbcfg_name ; 
 int rbcfg_open () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (int,char const**) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, const char *argv[])
{
	const struct rbcfg_command *cmd = NULL;
	int ret;
	int i;

	rbcfg_name = (char *) argv[0];

	fixup_rbcfg_envs();

	if (argc < 2) {
		usage();
		return EXIT_FAILURE;
	}

	for (i = 0; i < ARRAY_SIZE(rbcfg_commands); i++) {
		if (strcmp(rbcfg_commands[i].command, argv[1]) == 0) {
			cmd = &rbcfg_commands[i];
			break;
		}
	}

	if (cmd == NULL) {
		fprintf(stderr, "unknown command '%s'\n", argv[1]);
		usage();
		return EXIT_FAILURE;
	}

	argc -= 2;
	argv += 2;

	if (cmd->flags & CMD_FLAG_USES_CFG) {
		ret = rbcfg_open();
		if (ret)
			return EXIT_FAILURE;
	}

	ret = cmd->exec(argc, argv);

	if (cmd->flags & CMD_FLAG_USES_CFG)
		rbcfg_close();

	if (ret)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
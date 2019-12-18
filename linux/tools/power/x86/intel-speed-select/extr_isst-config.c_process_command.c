#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* feature; char* command; int /*<<< orphan*/  (* process_fn ) () ;} ;
struct TYPE_3__ {char* feature; int /*<<< orphan*/  (* process_fn ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  create_cpu_map () ; 
 int /*<<< orphan*/  debug_printf (char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* isst_cmds ; 
 TYPE_1__* isst_help_cmds ; 
 size_t optind ; 
 int /*<<< orphan*/  parse_cmd_args (int,size_t,char**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

void process_command(int argc, char **argv)
{
	int i = 0, matched = 0;
	char *feature = argv[optind];
	char *cmd = argv[optind + 1];

	if (!feature || !cmd)
		return;

	debug_printf("feature name [%s] command [%s]\n", feature, cmd);
	if (!strcmp(cmd, "-h") || !strcmp(cmd, "--help")) {
		while (isst_help_cmds[i].feature) {
			if (!strcmp(isst_help_cmds[i].feature, feature)) {
				isst_help_cmds[i].process_fn();
				exit(0);
			}
			++i;
		}
	}

	create_cpu_map();

	i = 0;
	while (isst_cmds[i].feature) {
		if (!strcmp(isst_cmds[i].feature, feature) &&
		    !strcmp(isst_cmds[i].command, cmd)) {
			parse_cmd_args(argc, optind + 1, argv);
			isst_cmds[i].process_fn();
			matched = 1;
			break;
		}
		++i;
	}

	if (!matched)
		fprintf(stderr, "Invalid command\n");
}
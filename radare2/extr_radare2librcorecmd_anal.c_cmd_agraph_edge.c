#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  graph; } ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RANode ;

/* Variables and functions */
 int /*<<< orphan*/  help_msg_age ; 
 int /*<<< orphan*/  r_agraph_add_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_agraph_del_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_agraph_get_node (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,...) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char** r_str_argv (char const*,int*) ; 
 int /*<<< orphan*/  r_str_argv_free (char**) ; 

__attribute__((used)) static void cmd_agraph_edge(RCore *core, const char *input) {
	switch (*input) {
	case ' ': // "age"
	case '-': { // "age-"
		RANode *u, *v;
		char **args;
		int n_args;

		args = r_str_argv (input + 1, &n_args);
		if (n_args != 2) {
			r_cons_printf ("Wrong arguments\n");
			r_str_argv_free (args);
			break;
		}

		u = r_agraph_get_node (core->graph, args[0]);
		v = r_agraph_get_node (core->graph, args[1]);
		if (!u || !v) {
			if (!u) {
				r_cons_printf ("Node %s not found!\n", args[0]);
			} else {
				r_cons_printf ("Node %s not found!\n", args[1]);
			}
			r_str_argv_free (args);
			break;
		}
		if (*input == ' ') {
			r_agraph_add_edge (core->graph, u, v);
		} else {
			r_agraph_del_edge (core->graph, u, v);
		}
		r_str_argv_free (args);
		break;
	}
	case '?':
	default:
		r_core_cmd_help (core, help_msg_age);
		break;
	}
}
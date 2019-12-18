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

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_agn ; 
 int /*<<< orphan*/  r_agraph_add_node_with_color (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  r_agraph_del_node (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ r_base64_decode_dyn (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_cons_printf (char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* r_str_append (char*,char*) ; 
 char** r_str_argv (char const*,int*) ; 
 int /*<<< orphan*/  r_str_argv_free (char**) ; 
 char* r_str_replace (char*,char*,char*,int) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void cmd_agraph_node(RCore *core, const char *input) {
	switch (*input) {
	case ' ': { // "agn"
		char *newbody = NULL;
		char **args, *body;
		int n_args, B_LEN = strlen ("base64:");
		int color = -1;
		input++;
		args = r_str_argv (input, &n_args);
		if (n_args < 1 || n_args > 3) {
			r_cons_printf ("Wrong arguments\n");
			r_str_argv_free (args);
			break;
		}
		// strdup cause there is double free in r_str_argv_free due to a realloc call
		if (n_args > 1) {
			body = strdup (args[1]);
			if (strncmp (body, "base64:", B_LEN) == 0) {
				body = r_str_replace (body, "\\n", "", true);
				newbody = (char *)r_base64_decode_dyn (body + B_LEN, -1);
				free (body);
				if (!newbody) {
					eprintf ("Cannot allocate buffer\n");
					r_str_argv_free (args);
					break;
				}
				body = newbody;
			}
			body = r_str_append (body, "\n");
			if (n_args > 2) {
			        color = atoi(args[2]);
			}
		} else {
			body = strdup ("");
		}
		r_agraph_add_node_with_color (core->graph, args[0], body, color);
		r_str_argv_free (args);
		free (body);
		//free newbody it's not necessary since r_str_append reallocate the space
		break;
	}
	case '-': { // "agn-"
		char **args;
		int n_args;

		input++;
		args = r_str_argv (input, &n_args);
		if (n_args != 1) {
			r_cons_printf ("Wrong arguments\n");
			r_str_argv_free (args);
			break;
		}
		r_agraph_del_node (core->graph, args[0]);
		r_str_argv_free (args);
		break;
	}
	case '?':
	default:
		r_core_cmd_help (core, help_msg_agn);
		break;
	}
}
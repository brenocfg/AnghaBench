#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* rcmd; TYPE_1__* num; } ;
struct TYPE_17__ {int /*<<< orphan*/  macro; } ;
struct TYPE_16__ {int value; } ;
struct TYPE_15__ {int is_html; } ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_STR_ISNOTEMPTY (char*) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_dot ; 
 int /*<<< orphan*/  r_cmd_macro_call (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_is_breaked () ; 
 int /*<<< orphan*/  r_cons_print (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*) ; 
 TYPE_14__* r_cons_singleton () ; 
 int /*<<< orphan*/  r_core_cmd (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  r_core_cmd_command (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd_repeat (TYPE_3__*,int) ; 
 char* r_core_cmd_str (TYPE_3__*,char*) ; 
 char* r_core_cmd_str_pipe (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  r_core_rtr_cmds (TYPE_3__*,char const*) ; 
 char* r_core_rtr_cmds_query (TYPE_3__*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  r_core_run_script (TYPE_3__*,char const*) ; 
 char* r_str_append (char*,char*) ; 
 char* r_str_trim_ro (char const*) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int cmd_interpret(void *data, const char *input) {
	char *str, *ptr, *eol, *rbuf, *filter, *inp;
	const char *host, *port, *cmd;
	RCore *core = (RCore *)data;

	switch (*input) {
	case '\0': // "."
		r_core_cmd_repeat (core, 0);
		break;
	case ':': // ".:"
		if ((ptr = strchr (input + 1, ' '))) {
			/* .:port cmd */
			/* .:host:port cmd */
			cmd = ptr + 1;
			*ptr = 0;
			eol = strchr (input + 1, ':');
			if (eol) {
				*eol = 0;
				host = input + 1;
				port = eol + 1;
			} else {
				host = "localhost";
				port = input + ((input[1] == ':')? 2: 1);
			}
			rbuf = r_core_rtr_cmds_query (core, host, port, cmd);
			if (rbuf) {
				r_cons_print (rbuf);
				free (rbuf);
			}
		} else {
			r_core_rtr_cmds (core, input + 1);
		}
		break;
	case '.': // ".." same as \n
		if (input[1] == '.') { // "..." run the last command repeated
			// same as \n with e cmd.repeat=true
			r_core_cmd_repeat (core, 1);
		} else if (input[1]) {
			char *str = r_core_cmd_str_pipe (core, r_str_trim_ro (input));
			if (str) {
				r_core_cmd (core, str, 0);
				free (str);
			}
		} else {
			eprintf ("Usage: .. ([file])\n");
		}
		break;
	case '*': // ".*"
		{
			const char *a = r_str_trim_ro (input + 1);
			char *s = strdup (a);
			char *sp = strchr (s, ' ');
			if (sp) {
				*sp = 0;
			}
			if (R_STR_ISNOTEMPTY (s)) {
				r_core_run_script (core, s);
			}
			free (s);
		}
		break;
	case '-': // ".-"
		if (input[1] == '?') {
			r_cons_printf ("Usage: '-' '.-' '. -' do the same\n");
		} else {
			r_core_run_script (core, "-");
		}
		break;
	case ' ': // ". "
		{
			const char *script_file = r_str_trim_ro (input + 1);
			if (*script_file == '$') {
				r_core_cmd0 (core, script_file);
			} else {
				if (!r_core_run_script (core, script_file)) {
					eprintf ("Cannot find script '%s'\n", script_file);
					core->num->value = 1;
				} else {
					core->num->value = 0;
				}
			}
		}
		break;
	case '!': // ".!"
		/* from command */
		r_core_cmd_command (core, input + 1);
		break;
	case '(': // ".("
		r_cmd_macro_call (&core->rcmd->macro, input + 1);
		break;
	case '?': // ".?"
		r_core_cmd_help (core, help_msg_dot);
		break;
	default:
		if (*input >= 0 && *input <= 9) {
			eprintf ("|ERROR| No .[0..9] to avoid infinite loops\n");
			break;
		}
		inp = strdup (input);
		filter = strchr (inp, '~');
		if (filter) {
			*filter = 0;
		}
		int tmp_html = r_cons_singleton ()->is_html;
		r_cons_singleton ()->is_html = 0;
		ptr = str = r_core_cmd_str (core, inp);
		r_cons_singleton ()->is_html = tmp_html;

		if (filter) {
			*filter = '~';
		}
		r_cons_break_push (NULL, NULL);
		if (ptr) {
			for (;;) {
				if (r_cons_is_breaked ()) {
					break;
				}
				eol = strchr (ptr, '\n');
				if (eol) {
					*eol = '\0';
				}
				if (*ptr) {
					char *p = r_str_append (strdup (ptr), filter);
					r_core_cmd0 (core, p);
					free (p);
				}
				if (!eol) {
					break;
				}
				ptr = eol + 1;
			}
		}
		r_cons_break_pop ();
		free (str);
		free (inp);
		break;
	}
	return 0;
}
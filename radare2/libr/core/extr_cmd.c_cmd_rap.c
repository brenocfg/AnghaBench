#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int cmdremote; int /*<<< orphan*/  io; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  aliascmd (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getArg (char const,char) ; 
 int /*<<< orphan*/  help_msg_equal ; 
 int /*<<< orphan*/  help_msg_equalg ; 
 int /*<<< orphan*/  help_msg_equalh ; 
 int /*<<< orphan*/  r_cons_printf (char*,char*) ; 
 int /*<<< orphan*/  r_cons_println (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_rtr_add (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_rtr_cmd (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_rtr_gdb (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_core_rtr_http (TYPE_1__*,int /*<<< orphan*/ ,char,char const*) ; 
 int /*<<< orphan*/  r_core_rtr_list (TYPE_1__*) ; 
 int /*<<< orphan*/  r_core_rtr_pushout (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_rtr_remove (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_rtr_session (TYPE_1__*,char const*) ; 
 char* r_io_system (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_str_bool (int) ; 
 char* r_str_trim_ro (char const*) ; 

__attribute__((used)) static int cmd_rap(void *data, const char *input) {
	RCore *core = (RCore *)data;
	switch (*input) {
	case '\0': // "="
		r_core_rtr_list (core);
		break;
	case 'j': // "=j"
		eprintf ("TODO: list connections in json\n");
		break;
	case '!': // "=!"
		if (input[1] == '=') {
			// swap core->cmdremote = core->cmdremote? 0: 1;
			core->cmdremote = input[2]? 1: 0;
			r_cons_println (r_str_bool (core->cmdremote));
		} else {
			char *res = r_io_system (core->io, input + 1);
			if (res) {
				r_cons_printf ("%s\n", res);
				free (res);
			}
		}
		break;
	case '$': // "=$"
		// XXX deprecate?
		aliascmd (core, input + 1);
		break;
	case '+': // "=+"
		r_core_rtr_add (core, input + 1);
		break;
	case '-': // "=-"
		r_core_rtr_remove (core, input + 1);
		break;
	//case ':': r_core_rtr_cmds (core, input + 1); break;
	case '<': // "=<"
		r_core_rtr_pushout (core, input + 1);
		break;
	case '=': // "=="
		r_core_rtr_session (core, input + 1);
		break;
	case 'g': // "=g"
		if (input[1] == '?') {
			r_core_cmd_help (core, help_msg_equalg);
		} else {
			r_core_rtr_gdb (core, getArg (input[1], 'g'), input + 1);
		}
		break;
	case 'h': // "=h"
		if (input[1] == '?') {
			r_core_cmd_help (core, help_msg_equalh);
		} else {
			r_core_rtr_http (core, getArg (input[1], 'h'), 'h', input + 1);
		}
		break;
	case 'H': // "=H"
		if (input[1] == '?') {
			r_core_cmd_help (core, help_msg_equalh);
		} else {
			const char *arg = r_str_trim_ro (input + 1);
			r_core_rtr_http (core, getArg (input[1], 'H'), 'H', arg);
		}
		break;
	case '?': // "=?"
		r_core_cmd_help (core, help_msg_equal);
		break;
	default:
		r_core_rtr_cmd (core, input);
		break;
	}
	return 0;
}
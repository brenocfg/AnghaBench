#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
struct TYPE_5__ {int /*<<< orphan*/  num; int /*<<< orphan*/  dbg; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int R_PERM_R ; 
 int R_PERM_W ; 
 int R_PERM_X ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char const** help_msg_de ; 
 char const** help_msg_des ; 
 int /*<<< orphan*/  r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  r_debug_esil_continue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_esil_prestep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_esil_step (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_debug_esil_watch (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  r_debug_esil_watch_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_esil_watch_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_esil_watch_reset (int /*<<< orphan*/ ) ; 
 int r_debug_reg_get (int /*<<< orphan*/ ,char*) ; 
 int r_num_math (int /*<<< orphan*/ ,char const*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void r_core_debug_esil (RCore *core, const char *input) {
	switch (input[0]) {
	case '\0': // "de"
		// list
		r_debug_esil_watch_list (core->dbg);
		break;
	case ' ': // "de "
		{
			char *line = strdup (input + 1);
			char *p, *q;
			int done = 0;
			int perm = 0, dev = 0;
			p = strchr (line, ' ');
			if (p) {
				*p++ = 0;
				if (strchr (line, 'r')) perm |= R_PERM_R;
				if (strchr (line, 'w')) perm |= R_PERM_W;
				if (strchr (line, 'x')) perm |= R_PERM_X;
				q = strchr (p, ' ');
				if (q) {
					*q++ = 0;
					dev = p[0];
					if (q) {
						r_debug_esil_watch (core->dbg, perm, dev, q);
						done = 1;
					}
				}
			}
			if (!done) {
				const char *help_de_msg[] = {
					"Usage:", "de", " [perm] [reg|mem] [expr]",
					NULL
				};
				r_core_cmd_help (core, help_de_msg);
			}
			free (line);
		}
		break;
	case '-': // "de-"
		r_debug_esil_watch_reset (core->dbg);
		break;
	case 'c': // "dec"
		if (r_debug_esil_watch_empty (core->dbg)) {
			eprintf ("Error: no esil watchpoints defined\n");
		} else {
			r_core_cmd0 (core, "aei");
			r_debug_esil_prestep (core->dbg, r_config_get_i (core->config, "esil.prestep"));
			r_debug_esil_continue (core->dbg);
		}
		break;
	case 's': // "des"
		if (input[1] == 'u' && input[2] == ' ') { // "desu"
			ut64 addr, naddr, fin = r_num_math (core->num, input + 2);
			r_core_cmd0 (core, "aei");
			addr = r_debug_reg_get (core->dbg, "PC");
			while (addr != fin) {
				r_debug_esil_prestep (core->dbg, r_config_get_i (
							core->config, "esil.prestep"));
				r_debug_esil_step (core->dbg, 1);
				naddr = r_debug_reg_get (core->dbg, "PC");
				if (naddr == addr) {
					eprintf ("Detected loophole\n");
					break;
				}
				addr = naddr;
			}
		} else if (input[1] == '?' || !input[1]) {
			r_core_cmd_help (core, help_msg_des);
		} else {
			r_core_cmd0 (core, "aei");
			r_debug_esil_prestep (core->dbg, r_config_get_i (core->config, "esil.prestep"));
			// continue
			r_debug_esil_step (core->dbg, r_num_math (core->num, input + 1));
		}
		break;
	case '?': // "de?"
	default:
		{
			r_core_cmd_help (core, help_msg_de);
			// TODO #7967 help refactor: move to detail
			r_cons_printf ("Examples:\n"
					" de r r rip       # stop when reads rip\n"
					" de rw m ADDR     # stop when read or write in ADDR\n"
					" de w r rdx       # stop when rdx register is modified\n"
					" de x m FROM..TO  # stop when rip in range\n");
		}
		break;
	}
}
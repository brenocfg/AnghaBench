#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct TYPE_8__ {TYPE_2__* dbg; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_DBG_SIGNAL_CONT ; 
 int /*<<< orphan*/  R_DBG_SIGNAL_SKIP ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_dk ; 
 int /*<<< orphan*/  help_msg_dko ; 
 int /*<<< orphan*/  r_cons_printf (char*,int) ; 
 int /*<<< orphan*/  r_cons_println (char const*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_kill (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_debug_kill_setup (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_signal_list (TYPE_2__*,int) ; 
 int /*<<< orphan*/  r_debug_signal_setup (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ ,char*) ; 
 int r_signal_from_string (char const*) ; 
 char* r_signal_to_string (int) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void r_core_debug_kill (RCore *core, const char *input) {
	if (!input || *input=='?') {
		if (input && input[1]) {
			const char *signame, *arg = input + 1;
			int signum = atoi (arg);
			if (signum > 0) {
				signame = r_signal_to_string (signum);
				if (signame)
					r_cons_println (signame);
			} else {
				signum = r_signal_from_string (arg);
				if (signum > 0) {
					r_cons_printf ("%d\n", signum);
				}
			}
		} else {
			r_core_cmd_help (core, help_msg_dk);
		}
	} else if (*input=='o') {
		switch (input[1]) {
			case 0: // "dko" - list signal skip/conts
				r_debug_signal_list (core->dbg, 1);
				break;
			case ' ': // dko SIGNAL
				if (input[2]) {
					char *p, *name = strdup (input + 2);
					int signum = atoi (name);
					p = strchr (name, ' ');
					if (p) *p++ = 0; /* got SIGNAL and an action */
					// Actions:
					//  - pass
					//  - trace
					//  - stop
					if (signum<1) signum = r_signal_from_string (name);
					if (signum>0) {
						if (!p || !p[0]) { // stop (the usual)
							r_debug_signal_setup (core->dbg, signum, 0);
						} else if (*p == 's') { // skip
							r_debug_signal_setup (core->dbg, signum, R_DBG_SIGNAL_SKIP);
						} else if (*p == 'c') { // cont
							r_debug_signal_setup (core->dbg, signum, R_DBG_SIGNAL_CONT);
						} else {
							eprintf ("Invalid option: %s\n", p);
						}
					} else {
						eprintf ("Invalid signal: %s\n", input + 2);
					}
					free (name);
					break;
				}
				/* fall through */
			case '?':
			default:
				{
					r_core_cmd_help (core, help_msg_dko);
					// TODO #7967 help refactor: move to detail
					r_cons_println ("NOTE: [signal] can be a number or a string that resolves with dk?\n"
							"  skip means do not enter into the signal handler\n"
							"  continue means enter into the signal handler");
				}
		}
	} else if (*input == 'j') {
		r_debug_signal_list (core->dbg, 2);
	} else if (!*input) {
		r_debug_signal_list (core->dbg, 0);
#if 0
		RListIter *iter;
		RDebugSignal *ds;
		eprintf ("TODO: list signal handlers of child\n");
		RList *list = r_debug_kill_list (core->dbg);
		r_list_foreach (list, iter, ds) {
			// TODO: resolve signal name by number and show handler offset
			eprintf ("--> %d\n", ds->num);
		}
		r_list_free (list);
#endif
	} else {
		int sig = atoi (input);
		char *p = strchr (input, '=');
		if (p) {
			r_debug_kill_setup (core->dbg, sig, r_num_math (core->num, p+1));
		} else {
			r_debug_kill (core->dbg, core->dbg->pid, core->dbg->tid, sig);
		}
	}
}
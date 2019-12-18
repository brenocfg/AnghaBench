#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct utsname {int /*<<< orphan*/  machine; int /*<<< orphan*/  release; int /*<<< orphan*/  nodename; int /*<<< orphan*/  sysname; } ;
struct TYPE_10__ {int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {int /*<<< orphan*/ * glob; int /*<<< orphan*/  minstamp; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ RCoreUndoCondition ;
typedef  int /*<<< orphan*/  RCoreUndo ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_uname (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  cmd_uniq (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_u ; 
 int /*<<< orphan*/  r_cons_printf (char*,...) ; 
 int /*<<< orphan*/  r_core_cmd_help (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmdf (void*,char*,char const*) ; 
 int /*<<< orphan*/ * r_core_undo_new (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_core_undo_pop (TYPE_2__*) ; 
 int /*<<< orphan*/  r_core_undo_print (TYPE_2__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  r_core_undo_push (TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  uname (struct utsname*) ; 

__attribute__((used)) static int cmd_undo(void *data, const char *input) {
	RCore *core = (RCore *)data;
	switch (input[0]) {
	case '?': // "u?"
		r_core_cmd_help (data, help_msg_u);
		return 1;
	case 'c': // "uc"
		switch (input[1]) {
		case ' ': {
			char *cmd = strdup (input + 2);
			char *rcmd = strchr (cmd, ',');
			if (rcmd) {
				*rcmd++ = 0;
				RCoreUndo *undo = r_core_undo_new (core->offset, cmd, rcmd);
				r_core_undo_push (core, undo);
			} else {
				eprintf ("Usage: uc [cmd] [revert-cmd]");
			}
			free (cmd);
			}
			break;
		case '?':
			eprintf ("Usage: uc [cmd],[revert-cmd]\n");
			eprintf (" uc. - list all reverts in current\n");
			eprintf (" uc* - list all core undos\n");
			eprintf (" uc  - list all core undos\n");
			eprintf (" uc- - undo last action\n");
			break;
		case '.': {
			RCoreUndoCondition cond = {
				.addr = core->offset,
				.minstamp = 0,
				.glob = NULL
			};
			r_core_undo_print (core, 1, &cond);
			} break;
		case '*':
			r_core_undo_print (core, 1, NULL);
			break;
		case '-': // "uc-"
			r_core_undo_pop (core);
			break;
		default:
			r_core_undo_print (core, 0, NULL);
			break;
		}
		return 1;
	case 's': // "us"
		r_core_cmdf (data, "s-%s", input + 1);
		return 1;
	case 'w': // "uw"
		r_core_cmdf (data, "wc%s", input + 1);
		return 1;
	case 'n': // "un"
		if (input[1] == 'a') { // "uname"
			(void)cmd_uname (core, input);
		} else if (input[1] == 'i' && input[2] == 'q') {
			(void)cmd_uniq (core, input);
		}
		return 1;
	}
#if __UNIX__
	struct utsname un;
	uname (&un);
	r_cons_printf ("%s %s %s %s\n", un.sysname,
		un.nodename, un.release, un.machine);
#elif __WINDOWS__
	r_cons_printf ("windows\n");
#else
	r_cons_printf ("unknown\n");
#endif
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int sync_index; TYPE_1__* log; } ;
struct TYPE_14__ {int /*<<< orphan*/  last; } ;
typedef  int /*<<< orphan*/  RCoreTask ;
typedef  int /*<<< orphan*/  RCoreLogCallback ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int atoi (char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getIndexFromLogString (char*) ; 
 int /*<<< orphan*/  help_msg_T ; 
 int /*<<< orphan*/  log_callback_all ; 
 int /*<<< orphan*/  log_callback_r2 ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_is_breaked () ; 
 int /*<<< orphan*/  r_cons_is_interactive () ; 
 int /*<<< orphan*/  r_cons_less_str (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_printf (char*,...) ; 
 void* r_cons_sleep_begin () ; 
 int /*<<< orphan*/  r_cons_sleep_end (void*) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_log_add (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  r_core_log_del (TYPE_2__*,int) ; 
 char* r_core_log_get (TYPE_2__*,int) ; 
 int /*<<< orphan*/  r_core_log_list (TYPE_2__*,int,int,char const) ; 
 int /*<<< orphan*/  r_core_log_run (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_task_enqueue (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_core_task_new (TYPE_2__*,int,char*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* r_file_slurp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_sys_sleep (int) ; 
 void* strchr (char const*,char) ; 
 int /*<<< orphan*/  textlog_chat (TYPE_2__*) ; 

__attribute__((used)) static int cmd_log(void *data, const char *input) {
	RCore *core = (RCore *) data;
	const char *arg, *input2;
	int n, n2;

	if (!input) {
		return 1;
	}

	input2 = (input && *input)? input + 1: "";
	arg = strchr (input2, ' ');
	n = atoi (input2);
	n2 = arg? atoi (arg + 1): 0;

	switch (*input) {
	case 'e': // "Te" shell: less
		{
			char *p = strchr (input, ' ');
			if (p) {
				char *b = r_file_slurp (p + 1, NULL);
				if (b) {
					r_cons_less_str (b, NULL);
					free (b);
				} else {
					eprintf ("File not found\n");
				}
			} else {
				eprintf ("Usage: less [filename]\n");
			}
		}
		break;
	case 'l': // "Tl"
		r_cons_printf ("%d\n", core->log->last - 1);
		break;
	case '-': //  "T-"
		r_core_log_del (core, n);
		break;
	case '?': // "T?"
		r_core_cmd_help (core, help_msg_T);
		break;
	case 'T': // "TT" Ts ? as ms?
		if (r_cons_is_interactive ()) {
			textlog_chat (core);
		} else {
			eprintf ("Only available when the screen is interactive\n");
		}
		break;
	case '=': // "T="
		if (input[1] == '&') { //  "T=&"
			if (input[2] == '&') { // "T=&&"
				r_cons_break_push (NULL, NULL);
				while (!r_cons_is_breaked ()) {
					r_core_cmd0 (core, "T=");
					void *bed = r_cons_sleep_begin();
					r_sys_sleep (1);
					r_cons_sleep_end (bed);
				}
				r_cons_break_pop ();
			} else {
				// TODO: Sucks that we can't enqueue functions, only commands
				eprintf ("Background thread syncing with http.sync started.\n");
				RCoreTask *task = r_core_task_new (core, true, "T=&&", NULL, core);
				r_core_task_enqueue (core, task);
			}
		} else {
			if (atoi (input + 1) > 0 || (input[1] == '0')) {
				core->sync_index = 0;
			} else {
				RCoreLogCallback log_callback = (input[1] == '*')
					? log_callback_all: log_callback_r2;
				char *res = r_core_log_get (core, core->sync_index);
				if (res) {
					int idx = getIndexFromLogString (res);
					if (idx != -1) {
						core->sync_index = idx + 1;
					}
					r_core_log_run (core, res, log_callback);
					free (res);
				} else {
					r_cons_printf ("Please check e http.sync\n");
				}
			}
		}
		break;
	case ' ': // "T "
		if (n > 0 || *input == '0') {
			r_core_log_list (core, n, n2, *input);
		} else {
			r_core_log_add (core, input + 1);
		}
		break;
	case 'm': // "Tm"
		if (n > 0) {
			r_core_log_list (core, n, 1, 't');
		} else {
			r_core_log_list (core, n, 0, 't');
		}
		break;
	case 'j': // "Tj"
	case '*':
	case '\0':
		r_core_log_list (core, n, n2, *input);
		break;
	}
	return 0;
}
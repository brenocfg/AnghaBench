#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  num; int /*<<< orphan*/  current_task; } ;
struct TYPE_17__ {int transient; int /*<<< orphan*/  res; } ;
typedef  TYPE_1__ RCoreTask ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  helpCmdTasks (TYPE_2__*) ; 
 int /*<<< orphan*/  r_cons_println (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_task_break (TYPE_2__*,int) ; 
 int /*<<< orphan*/  r_core_task_decref (TYPE_1__*) ; 
 int /*<<< orphan*/  r_core_task_del (TYPE_2__*,int) ; 
 int /*<<< orphan*/  r_core_task_del_all_done (TYPE_2__*) ; 
 int /*<<< orphan*/  r_core_task_enqueue (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* r_core_task_get_incref (TYPE_2__*,int) ; 
 int /*<<< orphan*/  r_core_task_join (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_task_list (TYPE_2__*,char const) ; 
 TYPE_1__* r_core_task_new (TYPE_2__*,int,char const*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int r_num_math (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_sandbox_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_tasks(void *data, const char *input) {
	RCore *core = (RCore*) data;
	switch (input[0]) {
	case '\0': // "&"
	case 'j': // "&j"
		r_core_task_list (core, *input);
		break;
	case 'b': { // "&b"
		if (r_sandbox_enable (0)) {
			eprintf ("This command is disabled in sandbox mode\n");
			return 0;
		}
		int tid = r_num_math (core->num, input + 1);
		if (tid) {
			r_core_task_break (core, tid);
		}
		break;
	}
	case '&': { // "&&"
		if (r_sandbox_enable (0)) {
			eprintf ("This command is disabled in sandbox mode\n");
			return 0;
		}
		int tid = r_num_math (core->num, input + 1);
		r_core_task_join (core, core->current_task, tid ? tid : -1);
		break;
	}
	case '=': { // "&="
		// r_core_task_list (core, '=');
		int tid = r_num_math (core->num, input + 1);
		if (tid) {
			RCoreTask *task = r_core_task_get_incref (core, tid);
			if (task) {
				if (task->res) {
					r_cons_println (task->res);
				}
				r_core_task_decref (task);
			} else {
				eprintf ("Cannot find task\n");
			}
		}
		break;
	}
	case '-': // "&-"
		if (r_sandbox_enable (0)) {
			eprintf ("This command is disabled in sandbox mode\n");
			return 0;
		}
		if (input[1] == '*') {
			r_core_task_del_all_done (core);
		} else {
			r_core_task_del (core, r_num_math (core->num, input + 1));
		}
		break;
	case '?': // "&?"
	default:
		helpCmdTasks (core);
		break;
	case ' ': // "& "
	case '_': // "&_"
	case 't': { // "&t"
		if (r_sandbox_enable (0)) {
			eprintf ("This command is disabled in sandbox mode\n");
			return 0;
		}
		RCoreTask *task = r_core_task_new (core, true, input + 1, NULL, core);
		if (!task) {
			break;
		}
		task->transient = input[0] == 't';
		r_core_task_enqueue (core, task);
		break;
	}
	}
	return 0;
}
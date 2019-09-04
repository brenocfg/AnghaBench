#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* id; void* offset; void* addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RAnalVTable ;
typedef  scalar_t__ RAnalClassErr ;

/* Variables and functions */
 scalar_t__ R_ANAL_CLASS_ERR_NONEXISTENT_CLASS ; 
 scalar_t__ R_ANAL_CLASS_ERR_SUCCESS ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_ac ; 
 int /*<<< orphan*/  r_anal_class_list_vtables (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ r_anal_class_vtable_delete (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ r_anal_class_vtable_set (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* r_num_get (int /*<<< orphan*/ ,char*) ; 
 char* r_str_trim_ro (char const*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void cmd_anal_class_vtable(RCore *core, const char *input) {
	RAnalClassErr err = R_ANAL_CLASS_ERR_SUCCESS;
	char c = input[0];
	switch (c) {
	case ' ': // "acv"
	case '-': { // "acv-"
		const char *str = r_str_trim_ro (input + 1);
		if (!*str) {
			eprintf ("No class name given.\n");
			return;
		}
		char *cstr = strdup (str);
		if (!cstr) {
			break;
		}
		char *end = strchr (cstr, ' ');
		if (end) {
			*end = '\0';
			end++;
		}

		if (!end || *end == '\0') {
			if (c == ' ') {
				r_anal_class_list_vtables (core->anal, cstr);
			} else /*if (c == '-')*/ {
				eprintf ("No vtable id given. See acv [class name].\n");
			}
			free (cstr);
			break;
		}

		char *arg1_str = end;
		end = strchr (arg1_str, ' ');
		if (end) {
			*end = '\0';
		}

		if (c == '-') {
			err = r_anal_class_vtable_delete (core->anal, cstr, arg1_str);
			free (cstr);
			break;
		}

		RAnalVTable vtable;
		vtable.id = NULL;
		vtable.addr = r_num_get (core->num, arg1_str);
		vtable.offset = 0;

		if (end) {
			vtable.offset = r_num_get (core->num, end + 1);
		}

		err = r_anal_class_vtable_set (core->anal, cstr, &vtable);
		free (vtable.id);
		free (cstr);
		break;
	}
	default:
		r_core_cmd_help (core, help_msg_ac);
		break;
	}

	if (err == R_ANAL_CLASS_ERR_NONEXISTENT_CLASS) {
		eprintf ("Class does not exist.\n");
	}
}
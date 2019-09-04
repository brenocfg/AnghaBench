#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RAnalClassErr ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_CLASS_ERR_CLASH ; 
 int /*<<< orphan*/  R_ANAL_CLASS_ERR_NONEXISTENT_CLASS ; 
 int /*<<< orphan*/  cmd_anal_class_base (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  cmd_anal_class_method (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  cmd_anal_class_vtable (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_ac ; 
 int /*<<< orphan*/  r_anal_class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_anal_class_delete (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_anal_class_list (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  r_anal_class_rename (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* r_str_trim_ro (char const*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void cmd_anal_classes(RCore *core, const char *input) {
	switch (input[0]) {
	case 'l': // "acl"
		r_anal_class_list (core->anal, input[1]);
		break;
	case ' ': // "ac"
	case '-': // "ac-"
	case 'n': { // "acn"
		const char *str = r_str_trim_ro (input + 1);
		if (!*str) {
			break;
		}
		char *cstr = strdup (str);
		if (!cstr) {
			break;
		}
		char *end = strchr (cstr, ' ');
		if (end) {
			*end = '\0';
		}
		if (input[0] == '-') {
			r_anal_class_delete (core->anal, cstr);
		} else if(input[0] == 'n') {
			if (!end) {
				eprintf ("No new class name given.\n");
			} else {
				char *new_name = end + 1;
				end = strchr (new_name, ' ');
				if (end) {
					*end = '\0';
				}
				RAnalClassErr err = r_anal_class_rename (core->anal, cstr, new_name);
				if (err == R_ANAL_CLASS_ERR_NONEXISTENT_CLASS) {
					eprintf ("Class does not exist.\n");
				} else if (err == R_ANAL_CLASS_ERR_CLASH) {
					eprintf ("A class with this name already exists.\n");
				}
			}
		} else {
			r_anal_class_create (core->anal, cstr);
		}
		free (cstr);
		break;
	}
	case 'v':
		cmd_anal_class_vtable (core, input + 1);
		break;
	case 'b': // "acb"
		cmd_anal_class_base (core, input + 1);
		break;
	case 'm': // "acm"
		cmd_anal_class_method (core, input + 1);
		break;
	default: // "ac?"
		r_core_cmd_help (core, help_msg_ac);
		break;
	}
}
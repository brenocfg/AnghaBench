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
struct TYPE_4__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_av ; 
 char* r_anal_rtti_demangle_class_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_anal_rtti_print_all (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  r_anal_rtti_print_at_vtable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  r_anal_rtti_recover_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* r_str_trim_dup (char const*) ; 

__attribute__((used)) static void cmd_anal_rtti(RCore *core, const char *input) {
	switch (input[0]) {
	case '\0': // "avr"
	case 'j': // "avrj"
		r_anal_rtti_print_at_vtable (core->anal, core->offset, input[0]);
		break;
	case 'a': // "avra"
		r_anal_rtti_print_all (core->anal, input[1]);
		break;
	case 'r': // "avrr"
		r_anal_rtti_recover_all (core->anal);
		break;
	case 'D': { // "avrD"
		char *name = r_str_trim_dup (input + 1);
		char *demangled = r_anal_rtti_demangle_class_name (core->anal, name);
		free (name);
		if (demangled) {
			r_cons_println (demangled);
			free (demangled);
		}
		break;
	}
	default :
		r_core_cmd_help (core, help_msg_av);
		break;
	}
}
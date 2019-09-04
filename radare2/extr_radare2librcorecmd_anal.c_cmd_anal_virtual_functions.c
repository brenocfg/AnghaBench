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
struct TYPE_5__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_anal_rtti (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  help_msg_av ; 
 int /*<<< orphan*/  r_anal_list_vtables (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_anal_virtual_functions(RCore *core, const char* input) {
	switch (input[0]) {
	case '\0': // "av"
	case '*': // "av*"
	case 'j': // "avj"
		r_anal_list_vtables (core->anal, input[0]);
		break;
	case 'r': // "avr"
		cmd_anal_rtti (core, input + 1);
		break;
	default :
		r_core_cmd_help (core, help_msg_av);
		break;
	}
}
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
struct TYPE_4__ {int /*<<< orphan*/  rcmd; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_cmd_alias_del (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_cmd_alias_set (int /*<<< orphan*/ ,char const*,char*,int) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_1__*,char*) ; 

__attribute__((used)) static void aliascmd(RCore *core, const char *str) {
	switch (str[0]) {
	case '\0': // "=$"
		r_core_cmd0 (core, "$");
		break;
	case '-': // "=$-"
		if (str[1]) {
			r_cmd_alias_del (core->rcmd, str + 2);
		} else {
			r_cmd_alias_del (core->rcmd, NULL);
		//	r_cmd_alias_reset (core->rcmd);
		}
		break;
	case '?': // "=$?"
		eprintf ("Usage: =$[-][remotecmd]  # remote command alias\n");
		eprintf (" =$dr   # makes 'dr' alias for =!dr\n");
		eprintf (" =$-dr  # unset 'dr' alias\n");
		break;
	default:
		r_cmd_alias_set (core->rcmd, str, "", 1);
		break;
	}
}
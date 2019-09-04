#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  help_msg_Cvb ; 
 int /*<<< orphan*/  help_msg_Cvr ; 
 int /*<<< orphan*/  help_msg_Cvs ; 
 int /*<<< orphan*/  r_cons_printf (char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void r_comment_var_help(RCore *core, char type) {
	switch (type) {
	case 'b':
		r_core_cmd_help (core, help_msg_Cvb);
		break;
	case 's':
		r_core_cmd_help (core, help_msg_Cvs);
		break;
	case 'r':
		r_core_cmd_help (core, help_msg_Cvr);
		break;
	case '?':
		r_cons_printf("See Cvb?, Cvs? and Cvr?\n");
	}
}
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
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  help_msg_afv ; 
 int /*<<< orphan*/  help_msg_afvb ; 
 int /*<<< orphan*/  help_msg_afvr ; 
 int /*<<< orphan*/  help_msg_afvs ; 
 int /*<<< orphan*/  r_core_cmd_help (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void var_help(RCore *core, char ch) {
	switch (ch) {
	case 'b':
		r_core_cmd_help (core, help_msg_afvb);
		break;
	case 's':
		r_core_cmd_help (core, help_msg_afvs);
		break;
	case 'r':
		r_core_cmd_help (core, help_msg_afvr);
		break;
	case '?':
		r_core_cmd_help (core, help_msg_afv);
		break;
	default:
		eprintf ("See afv?, afvb?, afvr? and afvs?\n");
	}
}
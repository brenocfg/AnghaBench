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
 int /*<<< orphan*/  help_msg_z_slash ; 
 int /*<<< orphan*/  r_core_cmd_help (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int search (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int cmdSearch(void *data, const char *input) {
	RCore *core = (RCore *) data;

	switch (*input) {
	case 0:
	case '*':
		return search (core, input[0] == '*', false);
	case 'f':
		switch (input[1]) {
		case 0:
		case '*':
			return search (core, input[1] == '*', true);
		default:
			eprintf ("usage: z/[f*]\n");
			return false;
		}
	case '?':
		r_core_cmd_help (core, help_msg_z_slash);
		break;
	default:
		eprintf ("usage: z/[*]\n");
		return false;
	}

	return true;
}
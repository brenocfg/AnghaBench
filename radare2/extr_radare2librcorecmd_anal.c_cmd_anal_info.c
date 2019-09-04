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
 int /*<<< orphan*/  cmd_address_info (int /*<<< orphan*/ *,char const*,char) ; 
 int /*<<< orphan*/  eprintf (char*) ; 

__attribute__((used)) static void cmd_anal_info(RCore *core, const char *input) {
	switch (input[0]) {
	case '?':
		eprintf ("Usage: ai @ rsp\n");
		break;
	case ' ':
		cmd_address_info (core, input, 0);
		break;
	case 'j': // "aij"
		cmd_address_info (core, input + 1, 'j');
		break;
	default:
		cmd_address_info (core, NULL, 0);
		break;
	}
}
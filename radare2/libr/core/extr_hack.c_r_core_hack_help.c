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
 int /*<<< orphan*/  r_core_cmd_help (int /*<<< orphan*/  const*,char const**) ; 

void r_core_hack_help(const RCore *core) {
	const char* help_msg[] = {
		"wao", " [op]", "performs a modification on current opcode",
		"wao", " nop", "nop current opcode",
		"wao", " jinf", "assemble an infinite loop",
		"wao", " jz", "make current opcode conditional (zero)",
		"wao", " jnz", "make current opcode conditional (not zero)",
		"wao", " ret1", "make the current opcode return 1",
		"wao", " ret0", "make the current opcode return 0",
		"wao", " retn", "make the current opcode return -1",
		"wao", " nocj", "remove conditional operation from branch (make it unconditional)",
		"wao", " trap", "make the current opcode a trap",
		"wao", " recj", "reverse (swap) conditional branch instruction",
		"WIP:", "", "not all archs are supported and not all commands work on all archs",
		NULL
	};
	r_core_cmd_help (core, help_msg);
}
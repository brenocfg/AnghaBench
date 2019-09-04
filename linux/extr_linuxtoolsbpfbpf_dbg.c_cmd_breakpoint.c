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

/* Variables and functions */
 int CMD_ERR ; 
 int CMD_OK ; 
 int /*<<< orphan*/  bpf_disasm (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bpf_dump_breakpoints () ; 
 int /*<<< orphan*/ * bpf_image ; 
 unsigned int bpf_prog_len ; 
 int /*<<< orphan*/  bpf_prog_loaded () ; 
 int /*<<< orphan*/  bpf_reset_breakpoints () ; 
 int /*<<< orphan*/  bpf_set_breakpoints (unsigned int) ; 
 scalar_t__ matches (char*,char*) ; 
 int /*<<< orphan*/  rl_printf (char*) ; 
 scalar_t__ strlen (char*) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmd_breakpoint(char *subcmd)
{
	if (!bpf_prog_loaded())
		return CMD_ERR;
	if (strlen(subcmd) == 0)
		bpf_dump_breakpoints();
	else if (matches(subcmd, "reset") == 0)
		bpf_reset_breakpoints();
	else {
		unsigned int where = strtoul(subcmd, NULL, 10);

		if (where < bpf_prog_len) {
			bpf_set_breakpoints(where);
			rl_printf("breakpoint at: ");
			bpf_disasm(bpf_image[where], where);
		}
	}

	return CMD_OK;
}
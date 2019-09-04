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
 int /*<<< orphan*/  bpf_disasm (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bpf_disasm_all (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * bpf_image ; 
 unsigned long bpf_prog_len ; 
 int /*<<< orphan*/  bpf_prog_loaded () ; 
 scalar_t__ strlen (char*) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmd_disassemble(char *line_string)
{
	bool single_line = false;
	unsigned long line;

	if (!bpf_prog_loaded())
		return CMD_ERR;
	if (strlen(line_string) > 0 &&
	    (line = strtoul(line_string, NULL, 10)) < bpf_prog_len)
		single_line = true;
	if (single_line)
		bpf_disasm(bpf_image[line], line);
	else
		bpf_disasm_all(bpf_image, bpf_prog_len);

	return CMD_OK;
}
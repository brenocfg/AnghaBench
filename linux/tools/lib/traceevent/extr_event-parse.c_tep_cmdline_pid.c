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
struct tep_handle {int cmdline_count; struct tep_cmdline* cmdlines; } ;
struct tep_cmdline {int pid; } ;
struct cmdline_list {int pid; } ;

/* Variables and functions */

int tep_cmdline_pid(struct tep_handle *tep, struct tep_cmdline *cmdline)
{
	struct cmdline_list *cmdlist = (struct cmdline_list *)cmdline;

	if (!cmdline)
		return -1;

	/*
	 * If cmdlines have not been created yet, or cmdline is
	 * not part of the array, then treat it as a cmdlist instead.
	 */
	if (!tep->cmdlines ||
	    cmdline < tep->cmdlines ||
	    cmdline >= tep->cmdlines + tep->cmdline_count)
		return cmdlist->pid;

	return cmdline->pid;
}
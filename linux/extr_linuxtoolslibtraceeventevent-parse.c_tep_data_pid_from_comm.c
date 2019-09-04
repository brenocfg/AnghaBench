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
struct tep_handle {int cmdline_count; struct cmdline* cmdlines; } ;
struct cmdline {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 struct cmdline* pid_from_cmdlist (struct tep_handle*,char const*,struct cmdline*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct cmdline *tep_data_pid_from_comm(struct tep_handle *pevent, const char *comm,
				       struct cmdline *next)
{
	struct cmdline *cmdline;

	/*
	 * If the cmdlines have not been converted yet, then use
	 * the list.
	 */
	if (!pevent->cmdlines)
		return pid_from_cmdlist(pevent, comm, next);

	if (next) {
		/*
		 * The next pointer could have been still from
		 * a previous call before cmdlines were created
		 */
		if (next < pevent->cmdlines ||
		    next >= pevent->cmdlines + pevent->cmdline_count)
			next = NULL;
		else
			cmdline  = next++;
	}

	if (!next)
		cmdline = pevent->cmdlines;

	while (cmdline < pevent->cmdlines + pevent->cmdline_count) {
		if (strcmp(cmdline->comm, comm) == 0)
			return cmdline;
		cmdline++;
	}
	return NULL;
}
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
struct tep_cmdline {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 struct tep_cmdline* pid_from_cmdlist (struct tep_handle*,char const*,struct tep_cmdline*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct tep_cmdline *tep_data_pid_from_comm(struct tep_handle *tep, const char *comm,
					   struct tep_cmdline *next)
{
	struct tep_cmdline *cmdline;

	/*
	 * If the cmdlines have not been converted yet, then use
	 * the list.
	 */
	if (!tep->cmdlines)
		return pid_from_cmdlist(tep, comm, next);

	if (next) {
		/*
		 * The next pointer could have been still from
		 * a previous call before cmdlines were created
		 */
		if (next < tep->cmdlines ||
		    next >= tep->cmdlines + tep->cmdline_count)
			next = NULL;
		else
			cmdline  = next++;
	}

	if (!next)
		cmdline = tep->cmdlines;

	while (cmdline < tep->cmdlines + tep->cmdline_count) {
		if (strcmp(cmdline->comm, comm) == 0)
			return cmdline;
		cmdline++;
	}
	return NULL;
}
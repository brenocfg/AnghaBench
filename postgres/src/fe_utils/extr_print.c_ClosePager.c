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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _ (char*) ; 
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_sigpipe_trap () ; 
 int /*<<< orphan*/ * stdout ; 

void
ClosePager(FILE *pagerpipe)
{
	if (pagerpipe && pagerpipe != stdout)
	{
		/*
		 * If printing was canceled midstream, warn about it.
		 *
		 * Some pagers like less use Ctrl-C as part of their command set. Even
		 * so, we abort our processing and warn the user what we did.  If the
		 * pager quit as a result of the SIGINT, this message won't go
		 * anywhere ...
		 */
		if (cancel_pressed)
			fprintf(pagerpipe, _("Interrupted\n"));

		pclose(pagerpipe);
		restore_sigpipe_trap();
	}
}
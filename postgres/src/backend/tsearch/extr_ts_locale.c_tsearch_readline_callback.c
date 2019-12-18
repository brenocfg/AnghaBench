#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  lineno; scalar_t__ curline; } ;
typedef  TYPE_1__ tsearch_readline_state ;

/* Variables and functions */
 int /*<<< orphan*/  errcontext (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
tsearch_readline_callback(void *arg)
{
	tsearch_readline_state *stp = (tsearch_readline_state *) arg;

	/*
	 * We can't include the text of the config line for errors that occur
	 * during t_readline() itself.  This is only partly a consequence of our
	 * arms-length use of that routine: the major cause of such errors is
	 * encoding violations, and we daren't try to print error messages
	 * containing badly-encoded data.
	 */
	if (stp->curline)
		errcontext("line %d of configuration file \"%s\": \"%s\"",
				   stp->lineno,
				   stp->filename,
				   stp->curline);
	else
		errcontext("line %d of configuration file \"%s\"",
				   stp->lineno,
				   stp->filename);
}
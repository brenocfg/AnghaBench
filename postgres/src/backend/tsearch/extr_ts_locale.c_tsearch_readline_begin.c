#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* previous; void* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_4__ {char const* filename; TYPE_3__ cb; int /*<<< orphan*/ * curline; scalar_t__ lineno; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ tsearch_readline_state ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char const*,char*) ; 
 TYPE_3__* error_context_stack ; 
 int /*<<< orphan*/  tsearch_readline_callback ; 

bool
tsearch_readline_begin(tsearch_readline_state *stp,
					   const char *filename)
{
	if ((stp->fp = AllocateFile(filename, "r")) == NULL)
		return false;
	stp->filename = filename;
	stp->lineno = 0;
	stp->curline = NULL;
	/* Setup error traceback support for ereport() */
	stp->cb.callback = tsearch_readline_callback;
	stp->cb.arg = (void *) stp;
	stp->cb.previous = error_context_stack;
	error_context_stack = &stp->cb;
	return true;
}
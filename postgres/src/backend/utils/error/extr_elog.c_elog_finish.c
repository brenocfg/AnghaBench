#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* message_id; int /*<<< orphan*/  domain; scalar_t__ funcname; int /*<<< orphan*/  backtrace; int /*<<< orphan*/  assoc_context; int /*<<< orphan*/  lineno; int /*<<< orphan*/  filename; int /*<<< orphan*/  saved_errno; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STACK_DEPTH () ; 
 int /*<<< orphan*/  EVALUATE_MESSAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errfinish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* errordata ; 
 size_t errordata_stack_depth ; 
 int /*<<< orphan*/  errstart (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ matches_backtrace_functions (scalar_t__) ; 
 int /*<<< orphan*/  message ; 
 int /*<<< orphan*/  recursion_depth ; 
 int /*<<< orphan*/  set_backtrace (TYPE_1__*,int) ; 

void
elog_finish(int elevel, const char *fmt,...)
{
	ErrorData  *edata = &errordata[errordata_stack_depth];
	MemoryContext oldcontext;

	CHECK_STACK_DEPTH();

	/*
	 * Do errstart() to see if we actually want to report the message.
	 */
	errordata_stack_depth--;
	errno = edata->saved_errno;
	if (!errstart(elevel, edata->filename, edata->lineno, edata->funcname, NULL))
		return;					/* nothing to do */

	/*
	 * Format error message just like errmsg_internal().
	 */
	recursion_depth++;
	oldcontext = MemoryContextSwitchTo(edata->assoc_context);

	if (!edata->backtrace &&
		edata->funcname &&
		matches_backtrace_functions(edata->funcname))
		set_backtrace(edata, 2);

	edata->message_id = fmt;
	EVALUATE_MESSAGE(edata->domain, message, false, false);

	MemoryContextSwitchTo(oldcontext);
	recursion_depth--;

	/*
	 * And let errfinish() finish up.
	 */
	errfinish(0);
}
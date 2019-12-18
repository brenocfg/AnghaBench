#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;struct TYPE_7__* previous; } ;
struct TYPE_6__ {int elevel; scalar_t__ internalquery; scalar_t__ constraint_name; scalar_t__ datatype_name; scalar_t__ column_name; scalar_t__ table_name; scalar_t__ schema_name; scalar_t__ backtrace; scalar_t__ context; scalar_t__ hint; scalar_t__ detail_log; scalar_t__ detail; scalar_t__ message; scalar_t__ funcname; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ErrorData ;
typedef  TYPE_2__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CHECK_STACK_DEPTH () ; 
 scalar_t__ CritSectionCount ; 
 scalar_t__ DestNone ; 
 scalar_t__ DestRemote ; 
 int ERROR ; 
 int /*<<< orphan*/  EmitErrorReport () ; 
 int /*<<< orphan*/  ErrorContext ; 
 int FATAL ; 
 scalar_t__ InterruptHoldoffCount ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int PANIC ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/ * PG_exception_stack ; 
 scalar_t__ QueryCancelHoldoffCount ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ backtrace_functions ; 
 TYPE_2__* error_context_stack ; 
 TYPE_1__* errordata ; 
 size_t errordata_stack_depth ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ matches_backtrace_functions (scalar_t__) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 
 int /*<<< orphan*/  pq_endcopyout (int) ; 
 int /*<<< orphan*/  proc_exit (int) ; 
 int /*<<< orphan*/  recursion_depth ; 
 int /*<<< orphan*/  set_backtrace (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ whereToSendOutput ; 

void
errfinish(int dummy,...)
{
	ErrorData  *edata = &errordata[errordata_stack_depth];
	int			elevel;
	MemoryContext oldcontext;
	ErrorContextCallback *econtext;

	recursion_depth++;
	CHECK_STACK_DEPTH();
	elevel = edata->elevel;

	/*
	 * Do processing in ErrorContext, which we hope has enough reserved space
	 * to report an error.
	 */
	oldcontext = MemoryContextSwitchTo(ErrorContext);

	if (!edata->backtrace &&
		edata->funcname &&
		backtrace_functions &&
		matches_backtrace_functions(edata->funcname))
		set_backtrace(edata, 2);

	/*
	 * Call any context callback functions.  Errors occurring in callback
	 * functions will be treated as recursive errors --- this ensures we will
	 * avoid infinite recursion (see errstart).
	 */
	for (econtext = error_context_stack;
		 econtext != NULL;
		 econtext = econtext->previous)
		econtext->callback(econtext->arg);

	/*
	 * If ERROR (not more nor less) we pass it off to the current handler.
	 * Printing it and popping the stack is the responsibility of the handler.
	 */
	if (elevel == ERROR)
	{
		/*
		 * We do some minimal cleanup before longjmp'ing so that handlers can
		 * execute in a reasonably sane state.
		 *
		 * Reset InterruptHoldoffCount in case we ereport'd from inside an
		 * interrupt holdoff section.  (We assume here that no handler will
		 * itself be inside a holdoff section.  If necessary, such a handler
		 * could save and restore InterruptHoldoffCount for itself, but this
		 * should make life easier for most.)
		 */
		InterruptHoldoffCount = 0;
		QueryCancelHoldoffCount = 0;

		CritSectionCount = 0;	/* should be unnecessary, but... */

		/*
		 * Note that we leave CurrentMemoryContext set to ErrorContext. The
		 * handler should reset it to something else soon.
		 */

		recursion_depth--;
		PG_RE_THROW();
	}

	/*
	 * If we are doing FATAL or PANIC, abort any old-style COPY OUT in
	 * progress, so that we can report the message before dying.  (Without
	 * this, pq_putmessage will refuse to send the message at all, which is
	 * what we want for NOTICE messages, but not for fatal exits.) This hack
	 * is necessary because of poor design of old-style copy protocol.
	 */
	if (elevel >= FATAL && whereToSendOutput == DestRemote)
		pq_endcopyout(true);

	/* Emit the message to the right places */
	EmitErrorReport();

	/* Now free up subsidiary data attached to stack entry, and release it */
	if (edata->message)
		pfree(edata->message);
	if (edata->detail)
		pfree(edata->detail);
	if (edata->detail_log)
		pfree(edata->detail_log);
	if (edata->hint)
		pfree(edata->hint);
	if (edata->context)
		pfree(edata->context);
	if (edata->backtrace)
		pfree(edata->backtrace);
	if (edata->schema_name)
		pfree(edata->schema_name);
	if (edata->table_name)
		pfree(edata->table_name);
	if (edata->column_name)
		pfree(edata->column_name);
	if (edata->datatype_name)
		pfree(edata->datatype_name);
	if (edata->constraint_name)
		pfree(edata->constraint_name);
	if (edata->internalquery)
		pfree(edata->internalquery);

	errordata_stack_depth--;

	/* Exit error-handling context */
	MemoryContextSwitchTo(oldcontext);
	recursion_depth--;

	/*
	 * Perform error recovery action as specified by elevel.
	 */
	if (elevel == FATAL)
	{
		/*
		 * For a FATAL error, we let proc_exit clean up and exit.
		 *
		 * If we just reported a startup failure, the client will disconnect
		 * on receiving it, so don't send any more to the client.
		 */
		if (PG_exception_stack == NULL && whereToSendOutput == DestRemote)
			whereToSendOutput = DestNone;

		/*
		 * fflush here is just to improve the odds that we get to see the
		 * error message, in case things are so hosed that proc_exit crashes.
		 * Any other code you might be tempted to add here should probably be
		 * in an on_proc_exit or on_shmem_exit callback instead.
		 */
		fflush(stdout);
		fflush(stderr);

		/*
		 * Do normal process-exit cleanup, then return exit code 1 to indicate
		 * FATAL termination.  The postmaster may or may not consider this
		 * worthy of panic, depending on which subprocess returns it.
		 */
		proc_exit(1);
	}

	if (elevel >= PANIC)
	{
		/*
		 * Serious crash time. Postmaster will observe SIGABRT process exit
		 * status and kill the other backends too.
		 *
		 * XXX: what if we are *in* the postmaster?  abort() won't kill our
		 * children...
		 */
		fflush(stdout);
		fflush(stderr);
		abort();
	}

	/*
	 * Check for cancel/die interrupt first --- this is so that the user can
	 * stop a query emitting tons of notice or warning messages, even if it's
	 * in a loop that otherwise fails to check for interrupts.
	 */
	CHECK_FOR_INTERRUPTS();
}
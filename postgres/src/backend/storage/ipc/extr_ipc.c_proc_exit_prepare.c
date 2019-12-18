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
struct TYPE_2__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* function ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CritSectionCount ; 
 int /*<<< orphan*/  DEBUG3 ; 
 int InterruptHoldoffCount ; 
 int InterruptPending ; 
 int ProcDiePending ; 
 int QueryCancelPending ; 
 int /*<<< orphan*/ * debug_query_string ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/ * error_context_stack ; 
 scalar_t__ on_proc_exit_index ; 
 TYPE_1__* on_proc_exit_list ; 
 int proc_exit_inprogress ; 
 int /*<<< orphan*/  shmem_exit (int) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
proc_exit_prepare(int code)
{
	/*
	 * Once we set this flag, we are committed to exit.  Any ereport() will
	 * NOT send control back to the main loop, but right back here.
	 */
	proc_exit_inprogress = true;

	/*
	 * Forget any pending cancel or die requests; we're doing our best to
	 * close up shop already.  Note that the signal handlers will not set
	 * these flags again, now that proc_exit_inprogress is set.
	 */
	InterruptPending = false;
	ProcDiePending = false;
	QueryCancelPending = false;
	InterruptHoldoffCount = 1;
	CritSectionCount = 0;

	/*
	 * Also clear the error context stack, to prevent error callbacks from
	 * being invoked by any elog/ereport calls made during proc_exit. Whatever
	 * context they might want to offer is probably not relevant, and in any
	 * case they are likely to fail outright after we've done things like
	 * aborting any open transaction.  (In normal exit scenarios the context
	 * stack should be empty anyway, but it might not be in the case of
	 * elog(FATAL) for example.)
	 */
	error_context_stack = NULL;
	/* For the same reason, reset debug_query_string before it's clobbered */
	debug_query_string = NULL;

	/* do our shared memory exits first */
	shmem_exit(code);

	elog(DEBUG3, "proc_exit(%d): %d callbacks to make",
		 code, on_proc_exit_index);

	/*
	 * call all the registered callbacks.
	 *
	 * Note that since we decrement on_proc_exit_index each time, if a
	 * callback calls ereport(ERROR) or ereport(FATAL) then it won't be
	 * invoked again when control comes back here (nor will the
	 * previously-completed callbacks).  So, an infinite loop should not be
	 * possible.
	 */
	while (--on_proc_exit_index >= 0)
		on_proc_exit_list[on_proc_exit_index].function(code,
													   on_proc_exit_list[on_proc_exit_index].arg);

	on_proc_exit_index = 0;
}
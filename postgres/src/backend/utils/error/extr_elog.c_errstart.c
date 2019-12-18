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
struct TYPE_4__ {int elevel; int output_to_server; int output_to_client; char const* filename; int lineno; char const* funcname; char const* domain; char const* context_domain; int /*<<< orphan*/ * assoc_context; int /*<<< orphan*/  saved_errno; int /*<<< orphan*/  sqlerrcode; } ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 scalar_t__ ClientAuthInProgress ; 
 scalar_t__ CritSectionCount ; 
 scalar_t__ DestRemote ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERRCODE_SUCCESSFUL_COMPLETION ; 
 int /*<<< orphan*/  ERRCODE_WARNING ; 
 int ERROR ; 
 int ERRORDATA_STACK_SIZE ; 
 int /*<<< orphan*/ * ErrorContext ; 
 scalar_t__ ExitOnAnyError ; 
 int FATAL ; 
 int INFO ; 
 int LOG_SERVER_ONLY ; 
 int Max (int,int) ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ *) ; 
 int PANIC ; 
 char const* PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/ * PG_exception_stack ; 
 int WARNING ; 
 int client_min_messages ; 
 int /*<<< orphan*/ * debug_query_string ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * error_context_stack ; 
 TYPE_1__* errordata ; 
 int errordata_stack_depth ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ in_error_recursion_trouble () ; 
 int is_log_level_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_min_messages ; 
 scalar_t__ proc_exit_inprogress ; 
 int /*<<< orphan*/  recursion_depth ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ whereToSendOutput ; 
 int /*<<< orphan*/  write_stderr (char*,char const*,int) ; 

bool
errstart(int elevel, const char *filename, int lineno,
		 const char *funcname, const char *domain)
{
	ErrorData  *edata;
	bool		output_to_server;
	bool		output_to_client = false;
	int			i;

	/*
	 * Check some cases in which we want to promote an error into a more
	 * severe error.  None of this logic applies for non-error messages.
	 */
	if (elevel >= ERROR)
	{
		/*
		 * If we are inside a critical section, all errors become PANIC
		 * errors.  See miscadmin.h.
		 */
		if (CritSectionCount > 0)
			elevel = PANIC;

		/*
		 * Check reasons for treating ERROR as FATAL:
		 *
		 * 1. we have no handler to pass the error to (implies we are in the
		 * postmaster or in backend startup).
		 *
		 * 2. ExitOnAnyError mode switch is set (initdb uses this).
		 *
		 * 3. the error occurred after proc_exit has begun to run.  (It's
		 * proc_exit's responsibility to see that this doesn't turn into
		 * infinite recursion!)
		 */
		if (elevel == ERROR)
		{
			if (PG_exception_stack == NULL ||
				ExitOnAnyError ||
				proc_exit_inprogress)
				elevel = FATAL;
		}

		/*
		 * If the error level is ERROR or more, errfinish is not going to
		 * return to caller; therefore, if there is any stacked error already
		 * in progress it will be lost.  This is more or less okay, except we
		 * do not want to have a FATAL or PANIC error downgraded because the
		 * reporting process was interrupted by a lower-grade error.  So check
		 * the stack and make sure we panic if panic is warranted.
		 */
		for (i = 0; i <= errordata_stack_depth; i++)
			elevel = Max(elevel, errordata[i].elevel);
	}

	/*
	 * Now decide whether we need to process this report at all; if it's
	 * warning or less and not enabled for logging, just return false without
	 * starting up any error logging machinery.
	 */

	/* Determine whether message is enabled for server log output */
	output_to_server = is_log_level_output(elevel, log_min_messages);

	/* Determine whether message is enabled for client output */
	if (whereToSendOutput == DestRemote && elevel != LOG_SERVER_ONLY)
	{
		/*
		 * client_min_messages is honored only after we complete the
		 * authentication handshake.  This is required both for security
		 * reasons and because many clients can't handle NOTICE messages
		 * during authentication.
		 */
		if (ClientAuthInProgress)
			output_to_client = (elevel >= ERROR);
		else
			output_to_client = (elevel >= client_min_messages ||
								elevel == INFO);
	}

	/* Skip processing effort if non-error message will not be output */
	if (elevel < ERROR && !output_to_server && !output_to_client)
		return false;

	/*
	 * We need to do some actual work.  Make sure that memory context
	 * initialization has finished, else we can't do anything useful.
	 */
	if (ErrorContext == NULL)
	{
		/* Oops, hard crash time; very little we can do safely here */
		write_stderr("error occurred at %s:%d before error message processing is available\n",
					 filename ? filename : "(unknown file)", lineno);
		exit(2);
	}

	/*
	 * Okay, crank up a stack entry to store the info in.
	 */

	if (recursion_depth++ > 0 && elevel >= ERROR)
	{
		/*
		 * Oops, error during error processing.  Clear ErrorContext as
		 * discussed at top of file.  We will not return to the original
		 * error's reporter or handler, so we don't need it.
		 */
		MemoryContextReset(ErrorContext);

		/*
		 * Infinite error recursion might be due to something broken in a
		 * context traceback routine.  Abandon them too.  We also abandon
		 * attempting to print the error statement (which, if long, could
		 * itself be the source of the recursive failure).
		 */
		if (in_error_recursion_trouble())
		{
			error_context_stack = NULL;
			debug_query_string = NULL;
		}
	}
	if (++errordata_stack_depth >= ERRORDATA_STACK_SIZE)
	{
		/*
		 * Wups, stack not big enough.  We treat this as a PANIC condition
		 * because it suggests an infinite loop of errors during error
		 * recovery.
		 */
		errordata_stack_depth = -1; /* make room on stack */
		ereport(PANIC, (errmsg_internal("ERRORDATA_STACK_SIZE exceeded")));
	}

	/* Initialize data for this error frame */
	edata = &errordata[errordata_stack_depth];
	MemSet(edata, 0, sizeof(ErrorData));
	edata->elevel = elevel;
	edata->output_to_server = output_to_server;
	edata->output_to_client = output_to_client;
	if (filename)
	{
		const char *slash;

		/* keep only base name, useful especially for vpath builds */
		slash = strrchr(filename, '/');
		if (slash)
			filename = slash + 1;
	}
	edata->filename = filename;
	edata->lineno = lineno;
	edata->funcname = funcname;
	/* the default text domain is the backend's */
	edata->domain = domain ? domain : PG_TEXTDOMAIN("postgres");
	/* initialize context_domain the same way (see set_errcontext_domain()) */
	edata->context_domain = edata->domain;
	/* Select default errcode based on elevel */
	if (elevel >= ERROR)
		edata->sqlerrcode = ERRCODE_INTERNAL_ERROR;
	else if (elevel == WARNING)
		edata->sqlerrcode = ERRCODE_WARNING;
	else
		edata->sqlerrcode = ERRCODE_SUCCESSFUL_COMPLETION;
	/* errno is saved here so that error parameter eval can't change it */
	edata->saved_errno = errno;

	/*
	 * Any allocations for this error state level should go into ErrorContext
	 */
	edata->assoc_context = ErrorContext;

	recursion_depth--;
	return true;
}
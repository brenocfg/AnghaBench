#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* filename; int lineno; char const* funcname; int /*<<< orphan*/ * assoc_context; int /*<<< orphan*/  saved_errno; } ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 scalar_t__ ERRORDATA_STACK_SIZE ; 
 int /*<<< orphan*/ * ErrorContext ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* errordata ; 
 scalar_t__ errordata_stack_depth ; 
 int /*<<< orphan*/  exit (int) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  write_stderr (char*,char const*,int) ; 

void
elog_start(const char *filename, int lineno, const char *funcname)
{
	ErrorData  *edata;

	/* Make sure that memory context initialization has finished */
	if (ErrorContext == NULL)
	{
		/* Oops, hard crash time; very little we can do safely here */
		write_stderr("error occurred at %s:%d before error message processing is available\n",
					 filename ? filename : "(unknown file)", lineno);
		exit(2);
	}

	if (++errordata_stack_depth >= ERRORDATA_STACK_SIZE)
	{
		/*
		 * Wups, stack not big enough.  We treat this as a PANIC condition
		 * because it suggests an infinite loop of errors during error
		 * recovery.  Note that the message is intentionally not localized,
		 * else failure to convert it to client encoding could cause further
		 * recursion.
		 */
		errordata_stack_depth = -1; /* make room on stack */
		ereport(PANIC, (errmsg_internal("ERRORDATA_STACK_SIZE exceeded")));
	}

	edata = &errordata[errordata_stack_depth];
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
	/* errno is saved now so that error parameter eval can't change it */
	edata->saved_errno = errno;

	/* Use ErrorContext for any allocations done at this level. */
	edata->assoc_context = ErrorContext;
}
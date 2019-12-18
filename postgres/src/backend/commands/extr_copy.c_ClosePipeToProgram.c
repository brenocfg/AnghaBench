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
struct TYPE_3__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  reached_eof; scalar_t__ is_copy_from; int /*<<< orphan*/  copy_file; int /*<<< orphan*/  is_program; } ;
typedef  TYPE_1__* CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int ClosePipeStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_EXTERNAL_ROUTINE_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errdetail_internal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ wait_result_is_signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_result_to_str (int) ; 

__attribute__((used)) static void
ClosePipeToProgram(CopyState cstate)
{
	int			pclose_rc;

	Assert(cstate->is_program);

	pclose_rc = ClosePipeStream(cstate->copy_file);
	if (pclose_rc == -1)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not close pipe to external command: %m")));
	else if (pclose_rc != 0)
	{
		/*
		 * If we ended a COPY FROM PROGRAM before reaching EOF, then it's
		 * expectable for the called program to fail with SIGPIPE, and we
		 * should not report that as an error.  Otherwise, SIGPIPE indicates a
		 * problem.
		 */
		if (cstate->is_copy_from && !cstate->reached_eof &&
			wait_result_is_signal(pclose_rc, SIGPIPE))
			return;

		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				 errmsg("program \"%s\" failed",
						cstate->filename),
				 errdetail_internal("%s", wait_result_to_str(pclose_rc))));
	}
}
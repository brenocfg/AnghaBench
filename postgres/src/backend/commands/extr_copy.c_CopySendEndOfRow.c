#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int copy_dest; int /*<<< orphan*/  binary; int /*<<< orphan*/  is_program; int /*<<< orphan*/  copy_file; TYPE_1__* fe_msgbuf; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  TYPE_2__* CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  COPY_CALLBACK 131 
#define  COPY_FILE 130 
#define  COPY_NEW_FE 129 
#define  COPY_OLD_FE 128 
 int /*<<< orphan*/  ClosePipeToProgram (TYPE_2__*) ; 
 int /*<<< orphan*/  CopySendChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  CopySendString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  ERRCODE_CONNECTION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ ) ; 
 int fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_putbytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_putmessage (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 

__attribute__((used)) static void
CopySendEndOfRow(CopyState cstate)
{
	StringInfo	fe_msgbuf = cstate->fe_msgbuf;

	switch (cstate->copy_dest)
	{
		case COPY_FILE:
			if (!cstate->binary)
			{
				/* Default line termination depends on platform */
#ifndef WIN32
				CopySendChar(cstate, '\n');
#else
				CopySendString(cstate, "\r\n");
#endif
			}

			if (fwrite(fe_msgbuf->data, fe_msgbuf->len, 1,
					   cstate->copy_file) != 1 ||
				ferror(cstate->copy_file))
			{
				if (cstate->is_program)
				{
					if (errno == EPIPE)
					{
						/*
						 * The pipe will be closed automatically on error at
						 * the end of transaction, but we might get a better
						 * error message from the subprocess' exit code than
						 * just "Broken Pipe"
						 */
						ClosePipeToProgram(cstate);

						/*
						 * If ClosePipeToProgram() didn't throw an error, the
						 * program terminated normally, but closed the pipe
						 * first. Restore errno, and throw an error.
						 */
						errno = EPIPE;
					}
					ereport(ERROR,
							(errcode_for_file_access(),
							 errmsg("could not write to COPY program: %m")));
				}
				else
					ereport(ERROR,
							(errcode_for_file_access(),
							 errmsg("could not write to COPY file: %m")));
			}
			break;
		case COPY_OLD_FE:
			/* The FE/BE protocol uses \n as newline for all platforms */
			if (!cstate->binary)
				CopySendChar(cstate, '\n');

			if (pq_putbytes(fe_msgbuf->data, fe_msgbuf->len))
			{
				/* no hope of recovering connection sync, so FATAL */
				ereport(FATAL,
						(errcode(ERRCODE_CONNECTION_FAILURE),
						 errmsg("connection lost during COPY to stdout")));
			}
			break;
		case COPY_NEW_FE:
			/* The FE/BE protocol uses \n as newline for all platforms */
			if (!cstate->binary)
				CopySendChar(cstate, '\n');

			/* Dump the accumulated row as one CopyData message */
			(void) pq_putmessage('d', fe_msgbuf->data, fe_msgbuf->len);
			break;
		case COPY_CALLBACK:
			Assert(false);		/* Not yet supported. */
			break;
	}

	resetStringInfo(fe_msgbuf);
}
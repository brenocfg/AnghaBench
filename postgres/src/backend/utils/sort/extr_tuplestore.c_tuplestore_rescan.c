#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t activeptr; int status; int /*<<< orphan*/  myfile; int /*<<< orphan*/  truncated; TYPE_2__* readptrs; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_5__ {int eflags; int eof_reached; long offset; int /*<<< orphan*/  file; int /*<<< orphan*/  current; } ;
typedef  TYPE_2__ TSReadPointer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufFileSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int EXEC_FLAG_REWIND ; 
 int /*<<< orphan*/  SEEK_SET ; 
#define  TSS_INMEM 130 
#define  TSS_READFILE 129 
#define  TSS_WRITEFILE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
tuplestore_rescan(Tuplestorestate *state)
{
	TSReadPointer *readptr = &state->readptrs[state->activeptr];

	Assert(readptr->eflags & EXEC_FLAG_REWIND);
	Assert(!state->truncated);

	switch (state->status)
	{
		case TSS_INMEM:
			readptr->eof_reached = false;
			readptr->current = 0;
			break;
		case TSS_WRITEFILE:
			readptr->eof_reached = false;
			readptr->file = 0;
			readptr->offset = 0L;
			break;
		case TSS_READFILE:
			readptr->eof_reached = false;
			if (BufFileSeek(state->myfile, 0, 0L, SEEK_SET) != 0)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not seek in tuplestore temporary file: %m")));
			break;
		default:
			elog(ERROR, "invalid tuplestore state");
			break;
	}
}
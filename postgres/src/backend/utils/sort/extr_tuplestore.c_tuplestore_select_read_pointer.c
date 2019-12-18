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
struct TYPE_4__ {int readptrcount; int activeptr; int status; int /*<<< orphan*/  myfile; int /*<<< orphan*/  writepos_offset; int /*<<< orphan*/  writepos_file; TYPE_2__* readptrs; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  file; int /*<<< orphan*/  eof_reached; } ;
typedef  TYPE_2__ TSReadPointer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufFileSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufFileTell (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SEEK_SET ; 
#define  TSS_INMEM 130 
#define  TSS_READFILE 129 
#define  TSS_WRITEFILE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
tuplestore_select_read_pointer(Tuplestorestate *state, int ptr)
{
	TSReadPointer *readptr;
	TSReadPointer *oldptr;

	Assert(ptr >= 0 && ptr < state->readptrcount);

	/* No work if already active */
	if (ptr == state->activeptr)
		return;

	readptr = &state->readptrs[ptr];
	oldptr = &state->readptrs[state->activeptr];

	switch (state->status)
	{
		case TSS_INMEM:
		case TSS_WRITEFILE:
			/* no work */
			break;
		case TSS_READFILE:

			/*
			 * First, save the current read position in the pointer about to
			 * become inactive.
			 */
			if (!oldptr->eof_reached)
				BufFileTell(state->myfile,
							&oldptr->file,
							&oldptr->offset);

			/*
			 * We have to make the temp file's seek position equal to the
			 * logical position of the new read pointer.  In eof_reached
			 * state, that's the EOF, which we have available from the saved
			 * write position.
			 */
			if (readptr->eof_reached)
			{
				if (BufFileSeek(state->myfile,
								state->writepos_file,
								state->writepos_offset,
								SEEK_SET) != 0)
					ereport(ERROR,
							(errcode_for_file_access(),
							 errmsg("could not seek in tuplestore temporary file: %m")));
			}
			else
			{
				if (BufFileSeek(state->myfile,
								readptr->file,
								readptr->offset,
								SEEK_SET) != 0)
					ereport(ERROR,
							(errcode_for_file_access(),
							 errmsg("could not seek in tuplestore temporary file: %m")));
			}
			break;
		default:
			elog(ERROR, "invalid tuplestore state");
			break;
	}

	state->activeptr = ptr;
}
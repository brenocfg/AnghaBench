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
struct TYPE_8__ {int status; int readptrcount; int activeptr; int backward; int eflags; int /*<<< orphan*/  writepos_offset; int /*<<< orphan*/  writepos_file; TYPE_2__* readptrs; int /*<<< orphan*/  myfile; int /*<<< orphan*/  interXact; int /*<<< orphan*/  resowner; int /*<<< orphan*/  memtupsize; int /*<<< orphan*/  memtupcount; void** memtuples; int /*<<< orphan*/  tuples; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_9__ {int eof_reached; int /*<<< orphan*/  offset; int /*<<< orphan*/  file; int /*<<< orphan*/  current; } ;
typedef  TYPE_2__ TSReadPointer ;
typedef  int /*<<< orphan*/  ResourceOwner ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufFileCreateTemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufFileSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufFileTell (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int EXEC_FLAG_BACKWARD ; 
 int /*<<< orphan*/  LACKMEM (TYPE_1__*) ; 
 int /*<<< orphan*/  PrepareTempTablespaces () ; 
 int /*<<< orphan*/  SEEK_SET ; 
#define  TSS_INMEM 130 
#define  TSS_READFILE 129 
#define  TSS_WRITEFILE 128 
 int /*<<< orphan*/  WRITETUP (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  dumptuples (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  grow_memtuples (TYPE_1__*) ; 

__attribute__((used)) static void
tuplestore_puttuple_common(Tuplestorestate *state, void *tuple)
{
	TSReadPointer *readptr;
	int			i;
	ResourceOwner oldowner;

	state->tuples++;

	switch (state->status)
	{
		case TSS_INMEM:

			/*
			 * Update read pointers as needed; see API spec above.
			 */
			readptr = state->readptrs;
			for (i = 0; i < state->readptrcount; readptr++, i++)
			{
				if (readptr->eof_reached && i != state->activeptr)
				{
					readptr->eof_reached = false;
					readptr->current = state->memtupcount;
				}
			}

			/*
			 * Grow the array as needed.  Note that we try to grow the array
			 * when there is still one free slot remaining --- if we fail,
			 * there'll still be room to store the incoming tuple, and then
			 * we'll switch to tape-based operation.
			 */
			if (state->memtupcount >= state->memtupsize - 1)
			{
				(void) grow_memtuples(state);
				Assert(state->memtupcount < state->memtupsize);
			}

			/* Stash the tuple in the in-memory array */
			state->memtuples[state->memtupcount++] = tuple;

			/*
			 * Done if we still fit in available memory and have array slots.
			 */
			if (state->memtupcount < state->memtupsize && !LACKMEM(state))
				return;

			/*
			 * Nope; time to switch to tape-based operation.  Make sure that
			 * the temp file(s) are created in suitable temp tablespaces.
			 */
			PrepareTempTablespaces();

			/* associate the file with the store's resource owner */
			oldowner = CurrentResourceOwner;
			CurrentResourceOwner = state->resowner;

			state->myfile = BufFileCreateTemp(state->interXact);

			CurrentResourceOwner = oldowner;

			/*
			 * Freeze the decision about whether trailing length words will be
			 * used.  We can't change this choice once data is on tape, even
			 * though callers might drop the requirement.
			 */
			state->backward = (state->eflags & EXEC_FLAG_BACKWARD) != 0;
			state->status = TSS_WRITEFILE;
			dumptuples(state);
			break;
		case TSS_WRITEFILE:

			/*
			 * Update read pointers as needed; see API spec above. Note:
			 * BufFileTell is quite cheap, so not worth trying to avoid
			 * multiple calls.
			 */
			readptr = state->readptrs;
			for (i = 0; i < state->readptrcount; readptr++, i++)
			{
				if (readptr->eof_reached && i != state->activeptr)
				{
					readptr->eof_reached = false;
					BufFileTell(state->myfile,
								&readptr->file,
								&readptr->offset);
				}
			}

			WRITETUP(state, tuple);
			break;
		case TSS_READFILE:

			/*
			 * Switch from reading to writing.
			 */
			if (!state->readptrs[state->activeptr].eof_reached)
				BufFileTell(state->myfile,
							&state->readptrs[state->activeptr].file,
							&state->readptrs[state->activeptr].offset);
			if (BufFileSeek(state->myfile,
							state->writepos_file, state->writepos_offset,
							SEEK_SET) != 0)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not seek in tuplestore temporary file: %m")));
			state->status = TSS_WRITEFILE;

			/*
			 * Update read pointers as needed; see API spec above.
			 */
			readptr = state->readptrs;
			for (i = 0; i < state->readptrcount; readptr++, i++)
			{
				if (readptr->eof_reached && i != state->activeptr)
				{
					readptr->eof_reached = false;
					readptr->file = state->writepos_file;
					readptr->offset = state->writepos_offset;
				}
			}

			WRITETUP(state, tuple);
			break;
		default:
			elog(ERROR, "invalid tuplestore state");
			break;
	}
}
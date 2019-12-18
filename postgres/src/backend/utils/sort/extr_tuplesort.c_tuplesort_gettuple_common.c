#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int status; int slabAllocatorUsed; int eof_reached; int /*<<< orphan*/  tapeset; int /*<<< orphan*/ * lastReturnedTuple; TYPE_2__* memtuples; int /*<<< orphan*/  memtupcount; int /*<<< orphan*/  result_tape; int /*<<< orphan*/  randomAccess; int /*<<< orphan*/  current; int /*<<< orphan*/  bound; int /*<<< orphan*/  bounded; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_16__ {int srctape; int /*<<< orphan*/ * tuple; } ;
typedef  TYPE_2__ SortTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 size_t LogicalTapeBackspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  LogicalTapeRewindForWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  READTUP (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RELEASE_SLAB_SLOT (TYPE_1__*,int /*<<< orphan*/ *) ; 
#define  TSS_FINALMERGE 130 
#define  TSS_SORTEDINMEM 129 
#define  TSS_SORTEDONTAPE 128 
 int /*<<< orphan*/  WORKER (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 unsigned int getlen (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mergereadnext (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  tuplesort_heap_delete_top (TYPE_1__*) ; 
 int /*<<< orphan*/  tuplesort_heap_replace_top (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static bool
tuplesort_gettuple_common(Tuplesortstate *state, bool forward,
						  SortTuple *stup)
{
	unsigned int tuplen;
	size_t		nmoved;

	Assert(!WORKER(state));

	switch (state->status)
	{
		case TSS_SORTEDINMEM:
			Assert(forward || state->randomAccess);
			Assert(!state->slabAllocatorUsed);
			if (forward)
			{
				if (state->current < state->memtupcount)
				{
					*stup = state->memtuples[state->current++];
					return true;
				}
				state->eof_reached = true;

				/*
				 * Complain if caller tries to retrieve more tuples than
				 * originally asked for in a bounded sort.  This is because
				 * returning EOF here might be the wrong thing.
				 */
				if (state->bounded && state->current >= state->bound)
					elog(ERROR, "retrieved too many tuples in a bounded sort");

				return false;
			}
			else
			{
				if (state->current <= 0)
					return false;

				/*
				 * if all tuples are fetched already then we return last
				 * tuple, else - tuple before last returned.
				 */
				if (state->eof_reached)
					state->eof_reached = false;
				else
				{
					state->current--;	/* last returned tuple */
					if (state->current <= 0)
						return false;
				}
				*stup = state->memtuples[state->current - 1];
				return true;
			}
			break;

		case TSS_SORTEDONTAPE:
			Assert(forward || state->randomAccess);
			Assert(state->slabAllocatorUsed);

			/*
			 * The slot that held the tuple that we returned in previous
			 * gettuple call can now be reused.
			 */
			if (state->lastReturnedTuple)
			{
				RELEASE_SLAB_SLOT(state, state->lastReturnedTuple);
				state->lastReturnedTuple = NULL;
			}

			if (forward)
			{
				if (state->eof_reached)
					return false;

				if ((tuplen = getlen(state, state->result_tape, true)) != 0)
				{
					READTUP(state, stup, state->result_tape, tuplen);

					/*
					 * Remember the tuple we return, so that we can recycle
					 * its memory on next call.  (This can be NULL, in the
					 * !state->tuples case).
					 */
					state->lastReturnedTuple = stup->tuple;

					return true;
				}
				else
				{
					state->eof_reached = true;
					return false;
				}
			}

			/*
			 * Backward.
			 *
			 * if all tuples are fetched already then we return last tuple,
			 * else - tuple before last returned.
			 */
			if (state->eof_reached)
			{
				/*
				 * Seek position is pointing just past the zero tuplen at the
				 * end of file; back up to fetch last tuple's ending length
				 * word.  If seek fails we must have a completely empty file.
				 */
				nmoved = LogicalTapeBackspace(state->tapeset,
											  state->result_tape,
											  2 * sizeof(unsigned int));
				if (nmoved == 0)
					return false;
				else if (nmoved != 2 * sizeof(unsigned int))
					elog(ERROR, "unexpected tape position");
				state->eof_reached = false;
			}
			else
			{
				/*
				 * Back up and fetch previously-returned tuple's ending length
				 * word.  If seek fails, assume we are at start of file.
				 */
				nmoved = LogicalTapeBackspace(state->tapeset,
											  state->result_tape,
											  sizeof(unsigned int));
				if (nmoved == 0)
					return false;
				else if (nmoved != sizeof(unsigned int))
					elog(ERROR, "unexpected tape position");
				tuplen = getlen(state, state->result_tape, false);

				/*
				 * Back up to get ending length word of tuple before it.
				 */
				nmoved = LogicalTapeBackspace(state->tapeset,
											  state->result_tape,
											  tuplen + 2 * sizeof(unsigned int));
				if (nmoved == tuplen + sizeof(unsigned int))
				{
					/*
					 * We backed up over the previous tuple, but there was no
					 * ending length word before it.  That means that the prev
					 * tuple is the first tuple in the file.  It is now the
					 * next to read in forward direction (not obviously right,
					 * but that is what in-memory case does).
					 */
					return false;
				}
				else if (nmoved != tuplen + 2 * sizeof(unsigned int))
					elog(ERROR, "bogus tuple length in backward scan");
			}

			tuplen = getlen(state, state->result_tape, false);

			/*
			 * Now we have the length of the prior tuple, back up and read it.
			 * Note: READTUP expects we are positioned after the initial
			 * length word of the tuple, so back up to that point.
			 */
			nmoved = LogicalTapeBackspace(state->tapeset,
										  state->result_tape,
										  tuplen);
			if (nmoved != tuplen)
				elog(ERROR, "bogus tuple length in backward scan");
			READTUP(state, stup, state->result_tape, tuplen);

			/*
			 * Remember the tuple we return, so that we can recycle its memory
			 * on next call. (This can be NULL, in the Datum case).
			 */
			state->lastReturnedTuple = stup->tuple;

			return true;

		case TSS_FINALMERGE:
			Assert(forward);
			/* We are managing memory ourselves, with the slab allocator. */
			Assert(state->slabAllocatorUsed);

			/*
			 * The slab slot holding the tuple that we returned in previous
			 * gettuple call can now be reused.
			 */
			if (state->lastReturnedTuple)
			{
				RELEASE_SLAB_SLOT(state, state->lastReturnedTuple);
				state->lastReturnedTuple = NULL;
			}

			/*
			 * This code should match the inner loop of mergeonerun().
			 */
			if (state->memtupcount > 0)
			{
				int			srcTape = state->memtuples[0].srctape;
				SortTuple	newtup;

				*stup = state->memtuples[0];

				/*
				 * Remember the tuple we return, so that we can recycle its
				 * memory on next call. (This can be NULL, in the Datum case).
				 */
				state->lastReturnedTuple = stup->tuple;

				/*
				 * Pull next tuple from tape, and replace the returned tuple
				 * at top of the heap with it.
				 */
				if (!mergereadnext(state, srcTape, &newtup))
				{
					/*
					 * If no more data, we've reached end of run on this tape.
					 * Remove the top node from the heap.
					 */
					tuplesort_heap_delete_top(state);

					/*
					 * Rewind to free the read buffer.  It'd go away at the
					 * end of the sort anyway, but better to release the
					 * memory early.
					 */
					LogicalTapeRewindForWrite(state->tapeset, srcTape);
					return true;
				}
				newtup.srctape = srcTape;
				tuplesort_heap_replace_top(state, &newtup);
				return true;
			}
			return false;

		default:
			elog(ERROR, "invalid tuplesort state");
			return false;		/* keep compiler quiet */
	}
}
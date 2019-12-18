#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int frozen; size_t max_size; int writing; int nbytes; size_t buffer_size; long firstBlockNumber; long nextBlockNumber; scalar_t__ pos; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  curBlockNumber; scalar_t__ dirty; } ;
struct TYPE_7__ {int nTapes; TYPE_2__* tapes; } ;
typedef  TYPE_1__ LogicalTapeSet ;
typedef  TYPE_2__ LogicalTape ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t BLCKSZ ; 
 int /*<<< orphan*/  TapeBlockSetNBytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ltsReadFillBuffer (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ltsWriteBlock (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * palloc (size_t) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

void
LogicalTapeRewindForRead(LogicalTapeSet *lts, int tapenum, size_t buffer_size)
{
	LogicalTape *lt;

	Assert(tapenum >= 0 && tapenum < lts->nTapes);
	lt = &lts->tapes[tapenum];

	/*
	 * Round and cap buffer_size if needed.
	 */
	if (lt->frozen)
		buffer_size = BLCKSZ;
	else
	{
		/* need at least one block */
		if (buffer_size < BLCKSZ)
			buffer_size = BLCKSZ;

		/* palloc() larger than max_size is unlikely to be helpful */
		if (buffer_size > lt->max_size)
			buffer_size = lt->max_size;

		/* round down to BLCKSZ boundary */
		buffer_size -= buffer_size % BLCKSZ;
	}

	if (lt->writing)
	{
		/*
		 * Completion of a write phase.  Flush last partial data block, and
		 * rewind for normal (destructive) read.
		 */
		if (lt->dirty)
		{
			/*
			 * As long as we've filled the buffer at least once, its contents
			 * are entirely defined from valgrind's point of view, even though
			 * contents beyond the current end point may be stale.  But it's
			 * possible - at least in the case of a parallel sort - to sort
			 * such small amount of data that we do not fill the buffer even
			 * once.  Tell valgrind that its contents are defined, so it
			 * doesn't bleat.
			 */
			VALGRIND_MAKE_MEM_DEFINED(lt->buffer + lt->nbytes,
									  lt->buffer_size - lt->nbytes);

			TapeBlockSetNBytes(lt->buffer, lt->nbytes);
			ltsWriteBlock(lts, lt->curBlockNumber, (void *) lt->buffer);
		}
		lt->writing = false;
	}
	else
	{
		/*
		 * This is only OK if tape is frozen; we rewind for (another) read
		 * pass.
		 */
		Assert(lt->frozen);
	}

	/* Allocate a read buffer (unless the tape is empty) */
	if (lt->buffer)
		pfree(lt->buffer);
	lt->buffer = NULL;
	lt->buffer_size = 0;
	if (lt->firstBlockNumber != -1L)
	{
		lt->buffer = palloc(buffer_size);
		lt->buffer_size = buffer_size;
	}

	/* Read the first block, or reset if tape is empty */
	lt->nextBlockNumber = lt->firstBlockNumber;
	lt->pos = 0;
	lt->nbytes = 0;
	ltsReadFillBuffer(lts, lt);
}
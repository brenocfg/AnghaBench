#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {long prev; long next; } ;
struct TYPE_8__ {int writing; long offsetBlockNumber; char* buffer; scalar_t__ buffer_size; int curBlockNumber; int firstBlockNumber; scalar_t__ pos; int dirty; scalar_t__ nbytes; } ;
struct TYPE_7__ {int nTapes; TYPE_2__* tapes; } ;
typedef  TYPE_1__ LogicalTapeSet ;
typedef  TYPE_2__ LogicalTape ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_5__* TapeBlockGetTrailer (char*) ; 
 scalar_t__ TapeBlockPayloadSize ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 void* ltsGetFreeBlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ltsWriteBlock (TYPE_1__*,int,void*) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 scalar_t__ palloc (scalar_t__) ; 

void
LogicalTapeWrite(LogicalTapeSet *lts, int tapenum,
				 void *ptr, size_t size)
{
	LogicalTape *lt;
	size_t		nthistime;

	Assert(tapenum >= 0 && tapenum < lts->nTapes);
	lt = &lts->tapes[tapenum];
	Assert(lt->writing);
	Assert(lt->offsetBlockNumber == 0L);

	/* Allocate data buffer and first block on first write */
	if (lt->buffer == NULL)
	{
		lt->buffer = (char *) palloc(BLCKSZ);
		lt->buffer_size = BLCKSZ;
	}
	if (lt->curBlockNumber == -1)
	{
		Assert(lt->firstBlockNumber == -1);
		Assert(lt->pos == 0);

		lt->curBlockNumber = ltsGetFreeBlock(lts);
		lt->firstBlockNumber = lt->curBlockNumber;

		TapeBlockGetTrailer(lt->buffer)->prev = -1L;
	}

	Assert(lt->buffer_size == BLCKSZ);
	while (size > 0)
	{
		if (lt->pos >= TapeBlockPayloadSize)
		{
			/* Buffer full, dump it out */
			long		nextBlockNumber;

			if (!lt->dirty)
			{
				/* Hmm, went directly from reading to writing? */
				elog(ERROR, "invalid logtape state: should be dirty");
			}

			/*
			 * First allocate the next block, so that we can store it in the
			 * 'next' pointer of this block.
			 */
			nextBlockNumber = ltsGetFreeBlock(lts);

			/* set the next-pointer and dump the current block. */
			TapeBlockGetTrailer(lt->buffer)->next = nextBlockNumber;
			ltsWriteBlock(lts, lt->curBlockNumber, (void *) lt->buffer);

			/* initialize the prev-pointer of the next block */
			TapeBlockGetTrailer(lt->buffer)->prev = lt->curBlockNumber;
			lt->curBlockNumber = nextBlockNumber;
			lt->pos = 0;
			lt->nbytes = 0;
		}

		nthistime = TapeBlockPayloadSize - lt->pos;
		if (nthistime > size)
			nthistime = size;
		Assert(nthistime > 0);

		memcpy(lt->buffer + lt->pos, ptr, nthistime);

		lt->dirty = true;
		lt->pos += nthistime;
		if (lt->nbytes < lt->pos)
			lt->nbytes = lt->pos;
		ptr = (void *) ((char *) ptr + nthistime);
		size -= nthistime;
	}
}
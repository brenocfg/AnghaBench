#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long next; } ;
struct TYPE_4__ {scalar_t__ nbytes; scalar_t__ buffer_size; char* buffer; long nextBlockNumber; long curBlockNumber; int /*<<< orphan*/  frozen; scalar_t__ offsetBlockNumber; scalar_t__ pos; } ;
typedef  int /*<<< orphan*/  LogicalTapeSet ;
typedef  TYPE_1__ LogicalTape ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 int TapeBlockGetNBytes (char*) ; 
 TYPE_3__* TapeBlockGetTrailer (char*) ; 
 scalar_t__ TapeBlockIsLast (char*) ; 
 int /*<<< orphan*/  ltsReadBlock (int /*<<< orphan*/ *,long,void*) ; 
 int /*<<< orphan*/  ltsReleaseBlock (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static bool
ltsReadFillBuffer(LogicalTapeSet *lts, LogicalTape *lt)
{
	lt->pos = 0;
	lt->nbytes = 0;

	do
	{
		char	   *thisbuf = lt->buffer + lt->nbytes;
		long		datablocknum = lt->nextBlockNumber;

		/* Fetch next block number */
		if (datablocknum == -1L)
			break;				/* EOF */
		/* Apply worker offset, needed for leader tapesets */
		datablocknum += lt->offsetBlockNumber;

		/* Read the block */
		ltsReadBlock(lts, datablocknum, (void *) thisbuf);
		if (!lt->frozen)
			ltsReleaseBlock(lts, datablocknum);
		lt->curBlockNumber = lt->nextBlockNumber;

		lt->nbytes += TapeBlockGetNBytes(thisbuf);
		if (TapeBlockIsLast(thisbuf))
		{
			lt->nextBlockNumber = -1L;
			/* EOF */
			break;
		}
		else
			lt->nextBlockNumber = TapeBlockGetTrailer(thisbuf)->next;

		/* Advance to next block, if we have buffer space left */
	} while (lt->buffer_size - lt->nbytes > BLCKSZ);

	return (lt->nbytes > 0);
}
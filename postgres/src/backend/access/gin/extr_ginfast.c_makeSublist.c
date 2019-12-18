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
typedef  int int32 ;
struct TYPE_3__ {int nPendingHeapTuples; int /*<<< orphan*/  nPendingPages; int /*<<< orphan*/  tailFreeSize; void* tail; void* head; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__ GinMetaPageData ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 void* BufferGetBlockNumber (scalar_t__) ; 
 int GinListPageSize ; 
 scalar_t__ GinNewBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexTupleSize (int /*<<< orphan*/ ) ; 
 void* InvalidBlockNumber ; 
 scalar_t__ InvalidBuffer ; 
 int MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeListPage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,void*) ; 

__attribute__((used)) static void
makeSublist(Relation index, IndexTuple *tuples, int32 ntuples,
			GinMetaPageData *res)
{
	Buffer		curBuffer = InvalidBuffer;
	Buffer		prevBuffer = InvalidBuffer;
	int			i,
				size = 0,
				tupsize;
	int			startTuple = 0;

	Assert(ntuples > 0);

	/*
	 * Split tuples into pages
	 */
	for (i = 0; i < ntuples; i++)
	{
		if (curBuffer == InvalidBuffer)
		{
			curBuffer = GinNewBuffer(index);

			if (prevBuffer != InvalidBuffer)
			{
				res->nPendingPages++;
				writeListPage(index, prevBuffer,
							  tuples + startTuple,
							  i - startTuple,
							  BufferGetBlockNumber(curBuffer));
			}
			else
			{
				res->head = BufferGetBlockNumber(curBuffer);
			}

			prevBuffer = curBuffer;
			startTuple = i;
			size = 0;
		}

		tupsize = MAXALIGN(IndexTupleSize(tuples[i])) + sizeof(ItemIdData);

		if (size + tupsize > GinListPageSize)
		{
			/* won't fit, force a new page and reprocess */
			i--;
			curBuffer = InvalidBuffer;
		}
		else
		{
			size += tupsize;
		}
	}

	/*
	 * Write last page
	 */
	res->tail = BufferGetBlockNumber(curBuffer);
	res->tailFreeSize = writeListPage(index, curBuffer,
									  tuples + startTuple,
									  ntuples - startTuple,
									  InvalidBlockNumber);
	res->nPendingPages++;
	/* that was only one heap tuple */
	res->nPendingHeapTuples = 1;
}
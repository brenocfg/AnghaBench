#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  writtenlen ;
struct TYPE_6__ {int /*<<< orphan*/  slabAllocatorUsed; int /*<<< orphan*/  tapeset; scalar_t__ randomAccess; int /*<<< orphan*/  datumTypeLen; int /*<<< orphan*/  tuples; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_7__ {void* tuple; int /*<<< orphan*/  datum1; scalar_t__ isnull1; } ;
typedef  TYPE_2__ SortTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FREEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (void*) ; 
 int /*<<< orphan*/  LogicalTapeWrite (int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  PointerGetDatum (void*) ; 
 unsigned int datumGetSize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (void*) ; 

__attribute__((used)) static void
writetup_datum(Tuplesortstate *state, int tapenum, SortTuple *stup)
{
	void	   *waddr;
	unsigned int tuplen;
	unsigned int writtenlen;

	if (stup->isnull1)
	{
		waddr = NULL;
		tuplen = 0;
	}
	else if (!state->tuples)
	{
		waddr = &stup->datum1;
		tuplen = sizeof(Datum);
	}
	else
	{
		waddr = stup->tuple;
		tuplen = datumGetSize(PointerGetDatum(stup->tuple), false, state->datumTypeLen);
		Assert(tuplen != 0);
	}

	writtenlen = tuplen + sizeof(unsigned int);

	LogicalTapeWrite(state->tapeset, tapenum,
					 (void *) &writtenlen, sizeof(writtenlen));
	LogicalTapeWrite(state->tapeset, tapenum,
					 waddr, tuplen);
	if (state->randomAccess)	/* need trailing length word? */
		LogicalTapeWrite(state->tapeset, tapenum,
						 (void *) &writtenlen, sizeof(writtenlen));

	if (!state->slabAllocatorUsed && stup->tuple)
	{
		FREEMEM(state, GetMemoryChunkSpace(stup->tuple));
		pfree(stup->tuple);
	}
}
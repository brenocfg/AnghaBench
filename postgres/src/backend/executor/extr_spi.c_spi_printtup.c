#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_4__ {TYPE_1__* tuptable; } ;
struct TYPE_3__ {int numvals; int alloced; int /*<<< orphan*/ * vals; int /*<<< orphan*/  tuptabcxt; } ;
typedef  TYPE_1__ SPITupleTable ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecCopySlotHeapTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_2__* _SPI_current ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ repalloc_huge (int /*<<< orphan*/ *,int) ; 

bool
spi_printtup(TupleTableSlot *slot, DestReceiver *self)
{
	SPITupleTable *tuptable;
	MemoryContext oldcxt;

	if (_SPI_current == NULL)
		elog(ERROR, "spi_printtup called while not connected to SPI");

	tuptable = _SPI_current->tuptable;
	if (tuptable == NULL)
		elog(ERROR, "improper call to spi_printtup");

	oldcxt = MemoryContextSwitchTo(tuptable->tuptabcxt);

	if (tuptable->numvals >= tuptable->alloced)
	{
		/* Double the size of the pointer array */
		uint64		newalloced = tuptable->alloced * 2;

		tuptable->vals = (HeapTuple *) repalloc_huge(tuptable->vals,
													 newalloced * sizeof(HeapTuple));
		tuptable->alloced = newalloced;
	}

	tuptable->vals[tuptable->numvals] = ExecCopySlotHeapTuple(slot);
	(tuptable->numvals)++;

	MemoryContextSwitchTo(oldcxt);

	return true;
}
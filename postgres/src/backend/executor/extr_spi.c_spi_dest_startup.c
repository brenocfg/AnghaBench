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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_4__ {int /*<<< orphan*/  tuptables; TYPE_1__* tuptable; } ;
struct TYPE_3__ {int alloced; int /*<<< orphan*/  tupdesc; scalar_t__ numvals; int /*<<< orphan*/ * vals; int /*<<< orphan*/  next; int /*<<< orphan*/  subid; int /*<<< orphan*/  tuptabcxt; } ;
typedef  TYPE_1__ SPITupleTable ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTupleDescCopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_2__* _SPI_current ; 
 int /*<<< orphan*/  _SPI_procmem () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  slist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
spi_dest_startup(DestReceiver *self, int operation, TupleDesc typeinfo)
{
	SPITupleTable *tuptable;
	MemoryContext oldcxt;
	MemoryContext tuptabcxt;

	if (_SPI_current == NULL)
		elog(ERROR, "spi_dest_startup called while not connected to SPI");

	if (_SPI_current->tuptable != NULL)
		elog(ERROR, "improper call to spi_dest_startup");

	/* We create the tuple table context as a child of procCxt */

	oldcxt = _SPI_procmem();	/* switch to procedure memory context */

	tuptabcxt = AllocSetContextCreate(CurrentMemoryContext,
									  "SPI TupTable",
									  ALLOCSET_DEFAULT_SIZES);
	MemoryContextSwitchTo(tuptabcxt);

	_SPI_current->tuptable = tuptable = (SPITupleTable *)
		palloc0(sizeof(SPITupleTable));
	tuptable->tuptabcxt = tuptabcxt;
	tuptable->subid = GetCurrentSubTransactionId();

	/*
	 * The tuptable is now valid enough to be freed by AtEOSubXact_SPI, so put
	 * it onto the SPI context's tuptables list.  This will ensure it's not
	 * leaked even in the unlikely event the following few lines fail.
	 */
	slist_push_head(&_SPI_current->tuptables, &tuptable->next);

	/* set up initial allocations */
	tuptable->alloced = 128;
	tuptable->vals = (HeapTuple *) palloc(tuptable->alloced * sizeof(HeapTuple));
	tuptable->numvals = 0;
	tuptable->tupdesc = CreateTupleDescCopy(typeinfo);

	MemoryContextSwitchTo(oldcxt);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int memtupcount; int /*<<< orphan*/  tupDesc; TYPE_1__* indexInfo; TYPE_3__* memtuples; TYPE_4__* sortKeys; int /*<<< orphan*/  tuplecontext; } ;
typedef  TYPE_2__ Tuplesortstate ;
struct TYPE_12__ {void* (* abbrev_converter ) (void*,TYPE_4__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  isnull1; void* datum1; void* tuple; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ii_IndexAttrNumbers; } ;
typedef  TYPE_3__ SortTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  scalar_t__ HeapTuple ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/  GetMemoryChunkSpace (scalar_t__) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEMEM (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consider_abort_common (TYPE_2__*) ; 
 scalar_t__ heap_copytuple (scalar_t__) ; 
 void* heap_getattr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* stub1 (void*,TYPE_4__*) ; 

__attribute__((used)) static void
copytup_cluster(Tuplesortstate *state, SortTuple *stup, void *tup)
{
	HeapTuple	tuple = (HeapTuple) tup;
	Datum		original;
	MemoryContext oldcontext = MemoryContextSwitchTo(state->tuplecontext);

	/* copy the tuple into sort storage */
	tuple = heap_copytuple(tuple);
	stup->tuple = (void *) tuple;
	USEMEM(state, GetMemoryChunkSpace(tuple));

	MemoryContextSwitchTo(oldcontext);

	/*
	 * set up first-column key value, and potentially abbreviate, if it's a
	 * simple column
	 */
	if (state->indexInfo->ii_IndexAttrNumbers[0] == 0)
		return;

	original = heap_getattr(tuple,
							state->indexInfo->ii_IndexAttrNumbers[0],
							state->tupDesc,
							&stup->isnull1);

	if (!state->sortKeys->abbrev_converter || stup->isnull1)
	{
		/*
		 * Store ordinary Datum representation, or NULL value.  If there is a
		 * converter it won't expect NULL values, and cost model is not
		 * required to account for NULL, so in that case we avoid calling
		 * converter and just set datum1 to zeroed representation (to be
		 * consistent, and to support cheap inequality tests for NULL
		 * abbreviated keys).
		 */
		stup->datum1 = original;
	}
	else if (!consider_abort_common(state))
	{
		/* Store abbreviated key representation */
		stup->datum1 = state->sortKeys->abbrev_converter(original,
														 state->sortKeys);
	}
	else
	{
		/* Abort abbreviation */
		int			i;

		stup->datum1 = original;

		/*
		 * Set state to be consistent with never trying abbreviation.
		 *
		 * Alter datum1 representation in already-copied tuples, so as to
		 * ensure a consistent representation (current tuple was just
		 * handled).  It does not matter if some dumped tuples are already
		 * sorted on tape, since serialized tuples lack abbreviated keys
		 * (TSS_BUILDRUNS state prevents control reaching here in any case).
		 */
		for (i = 0; i < state->memtupcount; i++)
		{
			SortTuple  *mtup = &state->memtuples[i];

			tuple = (HeapTuple) mtup->tuple;
			mtup->datum1 = heap_getattr(tuple,
										state->indexInfo->ii_IndexAttrNumbers[0],
										state->tupDesc,
										&mtup->isnull1);
		}
	}
}
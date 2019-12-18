#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int memtupcount; int /*<<< orphan*/  tupDesc; TYPE_5__* sortKeys; TYPE_2__* memtuples; int /*<<< orphan*/  tuplecontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_17__ {int /*<<< orphan*/  ssup_attno; void* (* abbrev_converter ) (void*,TYPE_5__*) ;} ;
struct TYPE_16__ {char* t_len; void* t_data; } ;
struct TYPE_15__ {int t_len; } ;
struct TYPE_14__ {int /*<<< orphan*/  isnull1; void* datum1; void* tuple; } ;
typedef  TYPE_2__ SortTuple ;
typedef  TYPE_3__* MinimalTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  void* HeapTupleHeader ;
typedef  TYPE_4__ HeapTupleData ;
typedef  void* Datum ;

/* Variables and functions */
 TYPE_3__* ExecCopySlotMinimalTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (TYPE_3__*) ; 
 char* MINIMAL_TUPLE_OFFSET ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consider_abort_common (TYPE_1__*) ; 
 void* heap_getattr (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* stub1 (void*,TYPE_5__*) ; 

__attribute__((used)) static void
copytup_heap(Tuplesortstate *state, SortTuple *stup, void *tup)
{
	/*
	 * We expect the passed "tup" to be a TupleTableSlot, and form a
	 * MinimalTuple using the exported interface for that.
	 */
	TupleTableSlot *slot = (TupleTableSlot *) tup;
	Datum		original;
	MinimalTuple tuple;
	HeapTupleData htup;
	MemoryContext oldcontext = MemoryContextSwitchTo(state->tuplecontext);

	/* copy the tuple into sort storage */
	tuple = ExecCopySlotMinimalTuple(slot);
	stup->tuple = (void *) tuple;
	USEMEM(state, GetMemoryChunkSpace(tuple));
	/* set up first-column key value */
	htup.t_len = tuple->t_len + MINIMAL_TUPLE_OFFSET;
	htup.t_data = (HeapTupleHeader) ((char *) tuple - MINIMAL_TUPLE_OFFSET);
	original = heap_getattr(&htup,
							state->sortKeys[0].ssup_attno,
							state->tupDesc,
							&stup->isnull1);

	MemoryContextSwitchTo(oldcontext);

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

			htup.t_len = ((MinimalTuple) mtup->tuple)->t_len +
				MINIMAL_TUPLE_OFFSET;
			htup.t_data = (HeapTupleHeader) ((char *) mtup->tuple -
											 MINIMAL_TUPLE_OFFSET);

			mtup->datum1 = heap_getattr(&htup,
										state->sortKeys[0].ssup_attno,
										state->tupDesc,
										&mtup->isnull1);
		}
	}
}
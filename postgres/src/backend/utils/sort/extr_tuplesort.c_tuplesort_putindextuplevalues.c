#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int memtupcount; int /*<<< orphan*/  indexRel; TYPE_2__* memtuples; TYPE_5__* sortKeys; int /*<<< orphan*/  sortcontext; int /*<<< orphan*/  tuplecontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_16__ {void* (* abbrev_converter ) (void*,TYPE_5__*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_14__ {scalar_t__ isnull1; void* datum1; TYPE_3__* tuple; } ;
typedef  TYPE_2__ SortTuple ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_3__* IndexTuple ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/  GetMemoryChunkSpace (TYPE_3__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consider_abort_common (TYPE_1__*) ; 
 TYPE_3__* index_form_tuple (int /*<<< orphan*/ ,void**,int*) ; 
 void* index_getattr (TYPE_3__*,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  puttuple_common (TYPE_1__*,TYPE_2__*) ; 
 void* stub1 (void*,TYPE_5__*) ; 

void
tuplesort_putindextuplevalues(Tuplesortstate *state, Relation rel,
							  ItemPointer self, Datum *values,
							  bool *isnull)
{
	MemoryContext oldcontext = MemoryContextSwitchTo(state->tuplecontext);
	SortTuple	stup;
	Datum		original;
	IndexTuple	tuple;

	stup.tuple = index_form_tuple(RelationGetDescr(rel), values, isnull);
	tuple = ((IndexTuple) stup.tuple);
	tuple->t_tid = *self;
	USEMEM(state, GetMemoryChunkSpace(stup.tuple));
	/* set up first-column key value */
	original = index_getattr(tuple,
							 1,
							 RelationGetDescr(state->indexRel),
							 &stup.isnull1);

	MemoryContextSwitchTo(state->sortcontext);

	if (!state->sortKeys || !state->sortKeys->abbrev_converter || stup.isnull1)
	{
		/*
		 * Store ordinary Datum representation, or NULL value.  If there is a
		 * converter it won't expect NULL values, and cost model is not
		 * required to account for NULL, so in that case we avoid calling
		 * converter and just set datum1 to zeroed representation (to be
		 * consistent, and to support cheap inequality tests for NULL
		 * abbreviated keys).
		 */
		stup.datum1 = original;
	}
	else if (!consider_abort_common(state))
	{
		/* Store abbreviated key representation */
		stup.datum1 = state->sortKeys->abbrev_converter(original,
														state->sortKeys);
	}
	else
	{
		/* Abort abbreviation */
		int			i;

		stup.datum1 = original;

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

			tuple = mtup->tuple;
			mtup->datum1 = index_getattr(tuple,
										 1,
										 RelationGetDescr(state->indexRel),
										 &mtup->isnull1);
		}
	}

	puttuple_common(state, &stup);

	MemoryContextSwitchTo(oldcontext);
}
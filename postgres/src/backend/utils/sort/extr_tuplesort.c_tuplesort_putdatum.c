#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int memtupcount; TYPE_2__* memtuples; TYPE_4__* sortKeys; int /*<<< orphan*/  sortcontext; int /*<<< orphan*/  datumTypeLen; int /*<<< orphan*/  tuples; int /*<<< orphan*/  tuplecontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_11__ {void* (* abbrev_converter ) (void*,TYPE_4__*) ;} ;
struct TYPE_10__ {int isnull1; int /*<<< orphan*/ * tuple; void* datum1; } ;
typedef  TYPE_2__ SortTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetPointer (void*) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 void* PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consider_abort_common (TYPE_1__*) ; 
 void* datumCopy (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puttuple_common (TYPE_1__*,TYPE_2__*) ; 
 void* stub1 (void*,TYPE_4__*) ; 

void
tuplesort_putdatum(Tuplesortstate *state, Datum val, bool isNull)
{
	MemoryContext oldcontext = MemoryContextSwitchTo(state->tuplecontext);
	SortTuple	stup;

	/*
	 * Pass-by-value types or null values are just stored directly in
	 * stup.datum1 (and stup.tuple is not used and set to NULL).
	 *
	 * Non-null pass-by-reference values need to be copied into memory we
	 * control, and possibly abbreviated. The copied value is pointed to by
	 * stup.tuple and is treated as the canonical copy (e.g. to return via
	 * tuplesort_getdatum or when writing to tape); stup.datum1 gets the
	 * abbreviated value if abbreviation is happening, otherwise it's
	 * identical to stup.tuple.
	 */

	if (isNull || !state->tuples)
	{
		/*
		 * Set datum1 to zeroed representation for NULLs (to be consistent,
		 * and to support cheap inequality tests for NULL abbreviated keys).
		 */
		stup.datum1 = !isNull ? val : (Datum) 0;
		stup.isnull1 = isNull;
		stup.tuple = NULL;		/* no separate storage */
		MemoryContextSwitchTo(state->sortcontext);
	}
	else
	{
		Datum		original = datumCopy(val, false, state->datumTypeLen);

		stup.isnull1 = false;
		stup.tuple = DatumGetPointer(original);
		USEMEM(state, GetMemoryChunkSpace(stup.tuple));
		MemoryContextSwitchTo(state->sortcontext);

		if (!state->sortKeys->abbrev_converter)
		{
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
			 * (TSS_BUILDRUNS state prevents control reaching here in any
			 * case).
			 */
			for (i = 0; i < state->memtupcount; i++)
			{
				SortTuple  *mtup = &state->memtuples[i];

				mtup->datum1 = PointerGetDatum(mtup->tuple);
			}
		}
	}

	puttuple_common(state, &stup);

	MemoryContextSwitchTo(oldcontext);
}
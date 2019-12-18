#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool
execTuplesUnequal(TupleTableSlot *slot1,
				  TupleTableSlot *slot2,
				  int numCols,
				  AttrNumber *matchColIdx,
				  FmgrInfo *eqfunctions,
				  const Oid *collations,
				  MemoryContext evalContext)
{
	MemoryContext oldContext;
	bool		result;
	int			i;

	/* Reset and switch into the temp context. */
	MemoryContextReset(evalContext);
	oldContext = MemoryContextSwitchTo(evalContext);

	/*
	 * We cannot report a match without checking all the fields, but we can
	 * report a non-match as soon as we find unequal fields.  So, start
	 * comparing at the last field (least significant sort key). That's the
	 * most likely to be different if we are dealing with sorted input.
	 */
	result = false;

	for (i = numCols; --i >= 0;)
	{
		AttrNumber	att = matchColIdx[i];
		Datum		attr1,
					attr2;
		bool		isNull1,
					isNull2;

		attr1 = slot_getattr(slot1, att, &isNull1);

		if (isNull1)
			continue;			/* can't prove anything here */

		attr2 = slot_getattr(slot2, att, &isNull2);

		if (isNull2)
			continue;			/* can't prove anything here */

		/* Apply the type-specific equality function */
		if (!DatumGetBool(FunctionCall2Coll(&eqfunctions[i],
											collations[i],
											attr1, attr2)))
		{
			result = true;		/* they are unequal */
			break;
		}
	}

	MemoryContextSwitchTo(oldContext);

	return result;
}
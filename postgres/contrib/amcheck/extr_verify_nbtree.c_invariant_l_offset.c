#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_11__ {int keysz; int /*<<< orphan*/ * scantid; int /*<<< orphan*/  heapkeyspace; int /*<<< orphan*/  pivotsearch; } ;
struct TYPE_10__ {int /*<<< orphan*/  rel; int /*<<< orphan*/  target; int /*<<< orphan*/  targetblock; } ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_1__ BtreeCheckState ;
typedef  TYPE_2__* BTScanInsert ;
typedef  scalar_t__ BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BTreeTupleGetHeapTIDCareful (TYPE_1__*,scalar_t__,int) ; 
 int BTreeTupleGetNKeyAtts (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ P_FIRSTDATAKEY (scalar_t__) ; 
 scalar_t__ P_ISLEAF (scalar_t__) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemIdCareful (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_compare (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int invariant_leq_offset (TYPE_1__*,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static inline bool
invariant_l_offset(BtreeCheckState *state, BTScanInsert key,
				   OffsetNumber upperbound)
{
	ItemId		itemid;
	int32		cmp;

	Assert(key->pivotsearch);

	/* Verify line pointer before checking tuple */
	itemid = PageGetItemIdCareful(state, state->targetblock, state->target,
								  upperbound);
	/* pg_upgrade'd indexes may legally have equal sibling tuples */
	if (!key->heapkeyspace)
		return invariant_leq_offset(state, key, upperbound);

	cmp = _bt_compare(state->rel, key, state->target, upperbound);

	/*
	 * _bt_compare() is capable of determining that a scankey with a
	 * filled-out attribute is greater than pivot tuples where the comparison
	 * is resolved at a truncated attribute (value of attribute in pivot is
	 * minus infinity).  However, it is not capable of determining that a
	 * scankey is _less than_ a tuple on the basis of a comparison resolved at
	 * _scankey_ minus infinity attribute.  Complete an extra step to simulate
	 * having minus infinity values for omitted scankey attribute(s).
	 */
	if (cmp == 0)
	{
		BTPageOpaque topaque;
		IndexTuple	ritup;
		int			uppnkeyatts;
		ItemPointer rheaptid;
		bool		nonpivot;

		ritup = (IndexTuple) PageGetItem(state->target, itemid);
		topaque = (BTPageOpaque) PageGetSpecialPointer(state->target);
		nonpivot = P_ISLEAF(topaque) && upperbound >= P_FIRSTDATAKEY(topaque);

		/* Get number of keys + heap TID for item to the right */
		uppnkeyatts = BTreeTupleGetNKeyAtts(ritup, state->rel);
		rheaptid = BTreeTupleGetHeapTIDCareful(state, ritup, nonpivot);

		/* Heap TID is tiebreaker key attribute */
		if (key->keysz == uppnkeyatts)
			return key->scantid == NULL && rheaptid != NULL;

		return key->keysz < uppnkeyatts;
	}

	return cmp < 0;
}
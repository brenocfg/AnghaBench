#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_9__ {int keysz; int /*<<< orphan*/ * scantid; int /*<<< orphan*/  heapkeyspace; int /*<<< orphan*/  pivotsearch; } ;
struct TYPE_8__ {int /*<<< orphan*/  rel; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_1__ BtreeCheckState ;
typedef  int /*<<< orphan*/  BlockNumber ;
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

__attribute__((used)) static inline bool
invariant_l_nontarget_offset(BtreeCheckState *state, BTScanInsert key,
							 BlockNumber nontargetblock, Page nontarget,
							 OffsetNumber upperbound)
{
	ItemId		itemid;
	int32		cmp;

	Assert(key->pivotsearch);

	/* Verify line pointer before checking tuple */
	itemid = PageGetItemIdCareful(state, nontargetblock, nontarget,
								  upperbound);
	cmp = _bt_compare(state->rel, key, nontarget, upperbound);

	/* pg_upgrade'd indexes may legally have equal sibling tuples */
	if (!key->heapkeyspace)
		return cmp <= 0;

	/* See invariant_l_offset() for an explanation of this extra step */
	if (cmp == 0)
	{
		IndexTuple	child;
		int			uppnkeyatts;
		ItemPointer childheaptid;
		BTPageOpaque copaque;
		bool		nonpivot;

		child = (IndexTuple) PageGetItem(nontarget, itemid);
		copaque = (BTPageOpaque) PageGetSpecialPointer(nontarget);
		nonpivot = P_ISLEAF(copaque) && upperbound >= P_FIRSTDATAKEY(copaque);

		/* Get number of keys + heap TID for child/non-target item */
		uppnkeyatts = BTreeTupleGetNKeyAtts(child, state->rel);
		childheaptid = BTreeTupleGetHeapTIDCareful(state, child, nonpivot);

		/* Heap TID is tiebreaker key attribute */
		if (key->keysz == uppnkeyatts)
			return key->scantid == NULL && childheaptid != NULL;

		return key->keysz < uppnkeyatts;
	}

	return cmp < 0;
}
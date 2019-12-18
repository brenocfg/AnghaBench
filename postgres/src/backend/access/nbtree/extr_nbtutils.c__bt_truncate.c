#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_21__ {int heapkeyspace; } ;
struct TYPE_20__ {int t_info; int /*<<< orphan*/  t_tid; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__* BTScanInsert ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BTreeTupleGetNAtts (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTreeTupleSetAltHeapTID (TYPE_1__*) ; 
 int /*<<< orphan*/  BTreeTupleSetNAtts (TYPE_1__*,int) ; 
 int INDEX_SIZE_MASK ; 
 int IndexRelationGetNumberOfAttributes (int /*<<< orphan*/ ) ; 
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int IndexTupleSize (TYPE_1__*) ; 
 scalar_t__ ItemPointerCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSetOffsetNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  OffsetNumberPrev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int _bt_keep_natts (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,TYPE_2__*) ; 
 TYPE_1__* index_truncate_tuple (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

IndexTuple
_bt_truncate(Relation rel, IndexTuple lastleft, IndexTuple firstright,
			 BTScanInsert itup_key)
{
	TupleDesc	itupdesc = RelationGetDescr(rel);
	int16		natts = IndexRelationGetNumberOfAttributes(rel);
	int16		nkeyatts = IndexRelationGetNumberOfKeyAttributes(rel);
	int			keepnatts;
	IndexTuple	pivot;
	ItemPointer pivotheaptid;
	Size		newsize;

	/*
	 * We should only ever truncate leaf index tuples.  It's never okay to
	 * truncate a second time.
	 */
	Assert(BTreeTupleGetNAtts(lastleft, rel) == natts);
	Assert(BTreeTupleGetNAtts(firstright, rel) == natts);

	/* Determine how many attributes must be kept in truncated tuple */
	keepnatts = _bt_keep_natts(rel, lastleft, firstright, itup_key);

#ifdef DEBUG_NO_TRUNCATE
	/* Force truncation to be ineffective for testing purposes */
	keepnatts = nkeyatts + 1;
#endif

	if (keepnatts <= natts)
	{
		IndexTuple	tidpivot;

		pivot = index_truncate_tuple(itupdesc, firstright, keepnatts);

		/*
		 * If there is a distinguishing key attribute within new pivot tuple,
		 * there is no need to add an explicit heap TID attribute
		 */
		if (keepnatts <= nkeyatts)
		{
			BTreeTupleSetNAtts(pivot, keepnatts);
			return pivot;
		}

		/*
		 * Only truncation of non-key attributes was possible, since key
		 * attributes are all equal.  It's necessary to add a heap TID
		 * attribute to the new pivot tuple.
		 */
		Assert(natts != nkeyatts);
		newsize = IndexTupleSize(pivot) + MAXALIGN(sizeof(ItemPointerData));
		tidpivot = palloc0(newsize);
		memcpy(tidpivot, pivot, IndexTupleSize(pivot));
		/* cannot leak memory here */
		pfree(pivot);
		pivot = tidpivot;
	}
	else
	{
		/*
		 * No truncation was possible, since key attributes are all equal.
		 * It's necessary to add a heap TID attribute to the new pivot tuple.
		 */
		Assert(natts == nkeyatts);
		newsize = IndexTupleSize(firstright) + MAXALIGN(sizeof(ItemPointerData));
		pivot = palloc0(newsize);
		memcpy(pivot, firstright, IndexTupleSize(firstright));
	}

	/*
	 * We have to use heap TID as a unique-ifier in the new pivot tuple, since
	 * no non-TID key attribute in the right item readily distinguishes the
	 * right side of the split from the left side.  Use enlarged space that
	 * holds a copy of first right tuple; place a heap TID value within the
	 * extra space that remains at the end.
	 *
	 * nbtree conceptualizes this case as an inability to truncate away any
	 * key attribute.  We must use an alternative representation of heap TID
	 * within pivots because heap TID is only treated as an attribute within
	 * nbtree (e.g., there is no pg_attribute entry).
	 */
	Assert(itup_key->heapkeyspace);
	pivot->t_info &= ~INDEX_SIZE_MASK;
	pivot->t_info |= newsize;

	/*
	 * Lehman & Yao use lastleft as the leaf high key in all cases, but don't
	 * consider suffix truncation.  It seems like a good idea to follow that
	 * example in cases where no truncation takes place -- use lastleft's heap
	 * TID.  (This is also the closest value to negative infinity that's
	 * legally usable.)
	 */
	pivotheaptid = (ItemPointer) ((char *) pivot + newsize -
								  sizeof(ItemPointerData));
	ItemPointerCopy(&lastleft->t_tid, pivotheaptid);

	/*
	 * Lehman and Yao require that the downlink to the right page, which is to
	 * be inserted into the parent page in the second phase of a page split be
	 * a strict lower bound on items on the right page, and a non-strict upper
	 * bound for items on the left page.  Assert that heap TIDs follow these
	 * invariants, since a heap TID value is apparently needed as a
	 * tiebreaker.
	 */
#ifndef DEBUG_NO_TRUNCATE
	Assert(ItemPointerCompare(&lastleft->t_tid, &firstright->t_tid) < 0);
	Assert(ItemPointerCompare(pivotheaptid, &lastleft->t_tid) >= 0);
	Assert(ItemPointerCompare(pivotheaptid, &firstright->t_tid) < 0);
#else

	/*
	 * Those invariants aren't guaranteed to hold for lastleft + firstright
	 * heap TID attribute values when they're considered here only because
	 * DEBUG_NO_TRUNCATE is defined (a heap TID is probably not actually
	 * needed as a tiebreaker).  DEBUG_NO_TRUNCATE must therefore use a heap
	 * TID value that always works as a strict lower bound for items to the
	 * right.  In particular, it must avoid using firstright's leading key
	 * attribute values along with lastleft's heap TID value when lastleft's
	 * TID happens to be greater than firstright's TID.
	 */
	ItemPointerCopy(&firstright->t_tid, pivotheaptid);

	/*
	 * Pivot heap TID should never be fully equal to firstright.  Note that
	 * the pivot heap TID will still end up equal to lastleft's heap TID when
	 * that's the only usable value.
	 */
	ItemPointerSetOffsetNumber(pivotheaptid,
							   OffsetNumberPrev(ItemPointerGetOffsetNumber(pivotheaptid)));
	Assert(ItemPointerCompare(pivotheaptid, &firstright->t_tid) < 0);
#endif

	BTreeTupleSetNAtts(pivot, nkeyatts);
	BTreeTupleSetAltHeapTID(pivot);

	return pivot;
}
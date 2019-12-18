#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_17__ {scalar_t__ itemsz; int bounds_valid; void* buf; TYPE_2__* itup_key; TYPE_1__* itup; } ;
struct TYPE_16__ {int /*<<< orphan*/ * scantid; scalar_t__ heapkeyspace; int /*<<< orphan*/  anynullkeys; } ;
struct TYPE_15__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  IndexUniqueCheck ;
typedef  TYPE_1__* IndexTuple ;
typedef  void* Buffer ;
typedef  int /*<<< orphan*/ * BTStack ;
typedef  TYPE_2__* BTScanInsert ;
typedef  scalar_t__ BTPageOpaque ;
typedef  TYPE_3__ BTInsertStateData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BT_WRITE ; 
 int /*<<< orphan*/  BufferGetPage (void*) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ ConditionalLockBuffer (void*) ; 
 int /*<<< orphan*/  IndexTupleSize (TYPE_1__*) ; 
 scalar_t__ InvalidBlockNumber ; 
 void* InvalidBuffer ; 
 scalar_t__ MAXALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ P_FIRSTDATAKEY (scalar_t__) ; 
 int /*<<< orphan*/  P_IGNORE (scalar_t__) ; 
 int /*<<< orphan*/  P_INCOMPLETE_SPLIT (scalar_t__) ; 
 scalar_t__ P_ISLEAF (scalar_t__) ; 
 scalar_t__ P_RIGHTMOST (scalar_t__) ; 
 scalar_t__ PageGetFreeSpace (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 void* ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RelationGetTargetBlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationSetTargetBlock (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (void*) ; 
 int /*<<< orphan*/  SpeculativeInsertionWait (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIQUE_CHECK_EXISTING ; 
 int /*<<< orphan*/  UNIQUE_CHECK_NO ; 
 int /*<<< orphan*/  XLTW_InsertIndex ; 
 int /*<<< orphan*/  XactLockTableWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_check_unique (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__*) ; 
 int /*<<< orphan*/  _bt_checkpage (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ _bt_compare (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _bt_findinsertloc (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_freestack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_insertonpg (int /*<<< orphan*/ ,TYPE_2__*,void*,void*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* _bt_mkscankey (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * _bt_search (int /*<<< orphan*/ ,TYPE_2__*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

bool
_bt_doinsert(Relation rel, IndexTuple itup,
			 IndexUniqueCheck checkUnique, Relation heapRel)
{
	bool		is_unique = false;
	BTInsertStateData insertstate;
	BTScanInsert itup_key;
	BTStack		stack = NULL;
	Buffer		buf;
	bool		fastpath;
	bool		checkingunique = (checkUnique != UNIQUE_CHECK_NO);

	/* we need an insertion scan key to do our search, so build one */
	itup_key = _bt_mkscankey(rel, itup);

	if (checkingunique)
	{
		if (!itup_key->anynullkeys)
		{
			/* No (heapkeyspace) scantid until uniqueness established */
			itup_key->scantid = NULL;
		}
		else
		{
			/*
			 * Scan key for new tuple contains NULL key values.  Bypass
			 * checkingunique steps.  They are unnecessary because core code
			 * considers NULL unequal to every value, including NULL.
			 *
			 * This optimization avoids O(N^2) behavior within the
			 * _bt_findinsertloc() heapkeyspace path when a unique index has a
			 * large number of "duplicates" with NULL key values.
			 */
			checkingunique = false;
			/* Tuple is unique in the sense that core code cares about */
			Assert(checkUnique != UNIQUE_CHECK_EXISTING);
			is_unique = true;
		}
	}

	/*
	 * Fill in the BTInsertState working area, to track the current page and
	 * position within the page to insert on
	 */
	insertstate.itup = itup;
	/* PageAddItem will MAXALIGN(), but be consistent */
	insertstate.itemsz = MAXALIGN(IndexTupleSize(itup));
	insertstate.itup_key = itup_key;
	insertstate.bounds_valid = false;
	insertstate.buf = InvalidBuffer;

	/*
	 * It's very common to have an index on an auto-incremented or
	 * monotonically increasing value. In such cases, every insertion happens
	 * towards the end of the index. We try to optimize that case by caching
	 * the right-most leaf of the index. If our cached block is still the
	 * rightmost leaf, has enough free space to accommodate a new entry and
	 * the insertion key is strictly greater than the first key in this page,
	 * then we can safely conclude that the new key will be inserted in the
	 * cached block. So we simply search within the cached block and insert
	 * the key at the appropriate location. We call it a fastpath.
	 *
	 * Testing has revealed, though, that the fastpath can result in increased
	 * contention on the exclusive-lock on the rightmost leaf page. So we
	 * conditionally check if the lock is available. If it's not available
	 * then we simply abandon the fastpath and take the regular path. This
	 * makes sense because unavailability of the lock also signals that some
	 * other backend might be concurrently inserting into the page, thus
	 * reducing our chances to finding an insertion place in this page.
	 */
top:
	fastpath = false;
	if (RelationGetTargetBlock(rel) != InvalidBlockNumber)
	{
		Page		page;
		BTPageOpaque lpageop;

		/*
		 * Conditionally acquire exclusive lock on the buffer before doing any
		 * checks. If we don't get the lock, we simply follow slowpath. If we
		 * do get the lock, this ensures that the index state cannot change,
		 * as far as the rightmost part of the index is concerned.
		 */
		buf = ReadBuffer(rel, RelationGetTargetBlock(rel));

		if (ConditionalLockBuffer(buf))
		{
			_bt_checkpage(rel, buf);

			page = BufferGetPage(buf);

			lpageop = (BTPageOpaque) PageGetSpecialPointer(page);

			/*
			 * Check if the page is still the rightmost leaf page, has enough
			 * free space to accommodate the new tuple, and the insertion scan
			 * key is strictly greater than the first key on the page.
			 */
			if (P_ISLEAF(lpageop) && P_RIGHTMOST(lpageop) &&
				!P_IGNORE(lpageop) &&
				(PageGetFreeSpace(page) > insertstate.itemsz) &&
				PageGetMaxOffsetNumber(page) >= P_FIRSTDATAKEY(lpageop) &&
				_bt_compare(rel, itup_key, page, P_FIRSTDATAKEY(lpageop)) > 0)
			{
				/*
				 * The right-most block should never have an incomplete split.
				 * But be paranoid and check for it anyway.
				 */
				Assert(!P_INCOMPLETE_SPLIT(lpageop));
				fastpath = true;
			}
			else
			{
				_bt_relbuf(rel, buf);

				/*
				 * Something did not work out. Just forget about the cached
				 * block and follow the normal path. It might be set again if
				 * the conditions are favourable.
				 */
				RelationSetTargetBlock(rel, InvalidBlockNumber);
			}
		}
		else
		{
			ReleaseBuffer(buf);

			/*
			 * If someone's holding a lock, it's likely to change anyway, so
			 * don't try again until we get an updated rightmost leaf.
			 */
			RelationSetTargetBlock(rel, InvalidBlockNumber);
		}
	}

	if (!fastpath)
	{
		/*
		 * Find the first page containing this key.  Buffer returned by
		 * _bt_search() is locked in exclusive mode.
		 */
		stack = _bt_search(rel, itup_key, &buf, BT_WRITE, NULL);
	}

	insertstate.buf = buf;
	buf = InvalidBuffer;		/* insertstate.buf now owns the buffer */

	/*
	 * If we're not allowing duplicates, make sure the key isn't already in
	 * the index.
	 *
	 * NOTE: obviously, _bt_check_unique can only detect keys that are already
	 * in the index; so it cannot defend against concurrent insertions of the
	 * same key.  We protect against that by means of holding a write lock on
	 * the first page the value could be on, with omitted/-inf value for the
	 * implicit heap TID tiebreaker attribute.  Any other would-be inserter of
	 * the same key must acquire a write lock on the same page, so only one
	 * would-be inserter can be making the check at one time.  Furthermore,
	 * once we are past the check we hold write locks continuously until we
	 * have performed our insertion, so no later inserter can fail to see our
	 * insertion.  (This requires some care in _bt_findinsertloc.)
	 *
	 * If we must wait for another xact, we release the lock while waiting,
	 * and then must start over completely.
	 *
	 * For a partial uniqueness check, we don't wait for the other xact. Just
	 * let the tuple in and return false for possibly non-unique, or true for
	 * definitely unique.
	 */
	if (checkingunique)
	{
		TransactionId xwait;
		uint32		speculativeToken;

		xwait = _bt_check_unique(rel, &insertstate, heapRel, checkUnique,
								 &is_unique, &speculativeToken);

		if (TransactionIdIsValid(xwait))
		{
			/* Have to wait for the other guy ... */
			_bt_relbuf(rel, insertstate.buf);
			insertstate.buf = InvalidBuffer;

			/*
			 * If it's a speculative insertion, wait for it to finish (ie. to
			 * go ahead with the insertion, or kill the tuple).  Otherwise
			 * wait for the transaction to finish as usual.
			 */
			if (speculativeToken)
				SpeculativeInsertionWait(xwait, speculativeToken);
			else
				XactLockTableWait(xwait, rel, &itup->t_tid, XLTW_InsertIndex);

			/* start over... */
			if (stack)
				_bt_freestack(stack);
			goto top;
		}

		/* Uniqueness is established -- restore heap tid as scantid */
		if (itup_key->heapkeyspace)
			itup_key->scantid = &itup->t_tid;
	}

	if (checkUnique != UNIQUE_CHECK_EXISTING)
	{
		OffsetNumber newitemoff;

		/*
		 * The only conflict predicate locking cares about for indexes is when
		 * an index tuple insert conflicts with an existing lock.  We don't
		 * know the actual page we're going to insert on for sure just yet in
		 * checkingunique and !heapkeyspace cases, but it's okay to use the
		 * first page the value could be on (with scantid omitted) instead.
		 */
		CheckForSerializableConflictIn(rel, NULL, insertstate.buf);

		/*
		 * Do the insertion.  Note that insertstate contains cached binary
		 * search bounds established within _bt_check_unique when insertion is
		 * checkingunique.
		 */
		newitemoff = _bt_findinsertloc(rel, &insertstate, checkingunique,
									   stack, heapRel);
		_bt_insertonpg(rel, itup_key, insertstate.buf, InvalidBuffer, stack,
					   itup, newitemoff, false);
	}
	else
	{
		/* just release the buffer */
		_bt_relbuf(rel, insertstate.buf);
	}

	/* be tidy */
	if (stack)
		_bt_freestack(stack);
	pfree(itup_key);

	return is_unique;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_20__ {scalar_t__ buf; int bounds_valid; scalar_t__ low; scalar_t__ stricthigh; TYPE_3__* itup_key; TYPE_2__* itup; } ;
struct TYPE_19__ {int /*<<< orphan*/  btpo_next; int /*<<< orphan*/  btpo_flags; } ;
struct TYPE_18__ {int /*<<< orphan*/ * scantid; int /*<<< orphan*/  anynullkeys; } ;
struct TYPE_17__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_16__ {int /*<<< orphan*/  speculativeToken; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; } ;
typedef  TYPE_1__ SnapshotData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexUniqueCheck ;
typedef  TYPE_2__* IndexTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  TYPE_3__* BTScanInsert ;
typedef  TYPE_4__* BTPageOpaque ;
typedef  TYPE_5__* BTInsertState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTP_HAS_GARBAGE ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 char* BuildIndexValueDescription (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERRCODE_UNIQUE_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  InitDirtySnapshot (TYPE_1__) ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemIdIsDead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdMarkDead (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (scalar_t__,int) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_4__*) ; 
 scalar_t__ P_HIKEY ; 
 int /*<<< orphan*/  P_IGNORE (TYPE_4__*) ; 
 scalar_t__ P_RIGHTMOST (TYPE_4__*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 TYPE_1__* SnapshotSelf ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIQUE_CHECK_EXISTING ; 
 scalar_t__ UNIQUE_CHECK_PARTIAL ; 
 scalar_t__ _bt_binsrch_insert (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ _bt_compare (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ _bt_relandgetbuf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errtableconstraint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_deform_tuple (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ table_index_fetch_tuple_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int*) ; 

__attribute__((used)) static TransactionId
_bt_check_unique(Relation rel, BTInsertState insertstate, Relation heapRel,
				 IndexUniqueCheck checkUnique, bool *is_unique,
				 uint32 *speculativeToken)
{
	IndexTuple	itup = insertstate->itup;
	BTScanInsert itup_key = insertstate->itup_key;
	SnapshotData SnapshotDirty;
	OffsetNumber offset;
	OffsetNumber maxoff;
	Page		page;
	BTPageOpaque opaque;
	Buffer		nbuf = InvalidBuffer;
	bool		found = false;

	/* Assume unique until we find a duplicate */
	*is_unique = true;

	InitDirtySnapshot(SnapshotDirty);

	page = BufferGetPage(insertstate->buf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	maxoff = PageGetMaxOffsetNumber(page);

	/*
	 * Find the first tuple with the same key.
	 *
	 * This also saves the binary search bounds in insertstate.  We use them
	 * in the fastpath below, but also in the _bt_findinsertloc() call later.
	 */
	Assert(!insertstate->bounds_valid);
	offset = _bt_binsrch_insert(rel, insertstate);

	/*
	 * Scan over all equal tuples, looking for live conflicts.
	 */
	Assert(!insertstate->bounds_valid || insertstate->low == offset);
	Assert(!itup_key->anynullkeys);
	Assert(itup_key->scantid == NULL);
	for (;;)
	{
		ItemId		curitemid;
		IndexTuple	curitup;
		BlockNumber nblkno;

		/*
		 * make sure the offset points to an actual item before trying to
		 * examine it...
		 */
		if (offset <= maxoff)
		{
			/*
			 * Fastpath: In most cases, we can use cached search bounds to
			 * limit our consideration to items that are definitely
			 * duplicates.  This fastpath doesn't apply when the original page
			 * is empty, or when initial offset is past the end of the
			 * original page, which may indicate that we need to examine a
			 * second or subsequent page.
			 *
			 * Note that this optimization allows us to avoid calling
			 * _bt_compare() directly when there are no duplicates, as long as
			 * the offset where the key will go is not at the end of the page.
			 */
			if (nbuf == InvalidBuffer && offset == insertstate->stricthigh)
			{
				Assert(insertstate->bounds_valid);
				Assert(insertstate->low >= P_FIRSTDATAKEY(opaque));
				Assert(insertstate->low <= insertstate->stricthigh);
				Assert(_bt_compare(rel, itup_key, page, offset) < 0);
				break;
			}

			curitemid = PageGetItemId(page, offset);

			/*
			 * We can skip items that are marked killed.
			 *
			 * In the presence of heavy update activity an index may contain
			 * many killed items with the same key; running _bt_compare() on
			 * each killed item gets expensive.  Just advance over killed
			 * items as quickly as we can.  We only apply _bt_compare() when
			 * we get to a non-killed item.  Even those comparisons could be
			 * avoided (in the common case where there is only one page to
			 * visit) by reusing bounds, but just skipping dead items is fast
			 * enough.
			 */
			if (!ItemIdIsDead(curitemid))
			{
				ItemPointerData htid;
				bool		all_dead;

				if (_bt_compare(rel, itup_key, page, offset) != 0)
					break;		/* we're past all the equal tuples */

				/* okay, we gotta fetch the heap tuple ... */
				curitup = (IndexTuple) PageGetItem(page, curitemid);
				htid = curitup->t_tid;

				/*
				 * If we are doing a recheck, we expect to find the tuple we
				 * are rechecking.  It's not a duplicate, but we have to keep
				 * scanning.
				 */
				if (checkUnique == UNIQUE_CHECK_EXISTING &&
					ItemPointerCompare(&htid, &itup->t_tid) == 0)
				{
					found = true;
				}

				/*
				 * Check if there's any table tuples for this index entry
				 * satisfying SnapshotDirty. This is necessary because for AMs
				 * with optimizations like heap's HOT, we have just a single
				 * index entry for the entire chain.
				 */
				else if (table_index_fetch_tuple_check(heapRel, &htid,
													   &SnapshotDirty,
													   &all_dead))
				{
					TransactionId xwait;

					/*
					 * It is a duplicate. If we are only doing a partial
					 * check, then don't bother checking if the tuple is being
					 * updated in another transaction. Just return the fact
					 * that it is a potential conflict and leave the full
					 * check till later. Don't invalidate binary search
					 * bounds.
					 */
					if (checkUnique == UNIQUE_CHECK_PARTIAL)
					{
						if (nbuf != InvalidBuffer)
							_bt_relbuf(rel, nbuf);
						*is_unique = false;
						return InvalidTransactionId;
					}

					/*
					 * If this tuple is being updated by other transaction
					 * then we have to wait for its commit/abort.
					 */
					xwait = (TransactionIdIsValid(SnapshotDirty.xmin)) ?
						SnapshotDirty.xmin : SnapshotDirty.xmax;

					if (TransactionIdIsValid(xwait))
					{
						if (nbuf != InvalidBuffer)
							_bt_relbuf(rel, nbuf);
						/* Tell _bt_doinsert to wait... */
						*speculativeToken = SnapshotDirty.speculativeToken;
						/* Caller releases lock on buf immediately */
						insertstate->bounds_valid = false;
						return xwait;
					}

					/*
					 * Otherwise we have a definite conflict.  But before
					 * complaining, look to see if the tuple we want to insert
					 * is itself now committed dead --- if so, don't complain.
					 * This is a waste of time in normal scenarios but we must
					 * do it to support CREATE INDEX CONCURRENTLY.
					 *
					 * We must follow HOT-chains here because during
					 * concurrent index build, we insert the root TID though
					 * the actual tuple may be somewhere in the HOT-chain.
					 * While following the chain we might not stop at the
					 * exact tuple which triggered the insert, but that's OK
					 * because if we find a live tuple anywhere in this chain,
					 * we have a unique key conflict.  The other live tuple is
					 * not part of this chain because it had a different index
					 * entry.
					 */
					htid = itup->t_tid;
					if (table_index_fetch_tuple_check(heapRel, &htid,
													  SnapshotSelf, NULL))
					{
						/* Normal case --- it's still live */
					}
					else
					{
						/*
						 * It's been deleted, so no error, and no need to
						 * continue searching
						 */
						break;
					}

					/*
					 * Check for a conflict-in as we would if we were going to
					 * write to this page.  We aren't actually going to write,
					 * but we want a chance to report SSI conflicts that would
					 * otherwise be masked by this unique constraint
					 * violation.
					 */
					CheckForSerializableConflictIn(rel, NULL, insertstate->buf);

					/*
					 * This is a definite conflict.  Break the tuple down into
					 * datums and report the error.  But first, make sure we
					 * release the buffer locks we're holding ---
					 * BuildIndexValueDescription could make catalog accesses,
					 * which in the worst case might touch this same index and
					 * cause deadlocks.
					 */
					if (nbuf != InvalidBuffer)
						_bt_relbuf(rel, nbuf);
					_bt_relbuf(rel, insertstate->buf);
					insertstate->buf = InvalidBuffer;
					insertstate->bounds_valid = false;

					{
						Datum		values[INDEX_MAX_KEYS];
						bool		isnull[INDEX_MAX_KEYS];
						char	   *key_desc;

						index_deform_tuple(itup, RelationGetDescr(rel),
										   values, isnull);

						key_desc = BuildIndexValueDescription(rel, values,
															  isnull);

						ereport(ERROR,
								(errcode(ERRCODE_UNIQUE_VIOLATION),
								 errmsg("duplicate key value violates unique constraint \"%s\"",
										RelationGetRelationName(rel)),
								 key_desc ? errdetail("Key %s already exists.",
													  key_desc) : 0,
								 errtableconstraint(heapRel,
													RelationGetRelationName(rel))));
					}
				}
				else if (all_dead)
				{
					/*
					 * The conflicting tuple (or whole HOT chain) is dead to
					 * everyone, so we may as well mark the index entry
					 * killed.
					 */
					ItemIdMarkDead(curitemid);
					opaque->btpo_flags |= BTP_HAS_GARBAGE;

					/*
					 * Mark buffer with a dirty hint, since state is not
					 * crucial. Be sure to mark the proper buffer dirty.
					 */
					if (nbuf != InvalidBuffer)
						MarkBufferDirtyHint(nbuf, true);
					else
						MarkBufferDirtyHint(insertstate->buf, true);
				}
			}
		}

		/*
		 * Advance to next tuple to continue checking.
		 */
		if (offset < maxoff)
			offset = OffsetNumberNext(offset);
		else
		{
			int			highkeycmp;

			/* If scankey == hikey we gotta check the next page too */
			if (P_RIGHTMOST(opaque))
				break;
			highkeycmp = _bt_compare(rel, itup_key, page, P_HIKEY);
			Assert(highkeycmp <= 0);
			if (highkeycmp != 0)
				break;
			/* Advance to next non-dead page --- there must be one */
			for (;;)
			{
				nblkno = opaque->btpo_next;
				nbuf = _bt_relandgetbuf(rel, nbuf, nblkno, BT_READ);
				page = BufferGetPage(nbuf);
				opaque = (BTPageOpaque) PageGetSpecialPointer(page);
				if (!P_IGNORE(opaque))
					break;
				if (P_RIGHTMOST(opaque))
					elog(ERROR, "fell off the end of index \"%s\"",
						 RelationGetRelationName(rel));
			}
			maxoff = PageGetMaxOffsetNumber(page);
			offset = P_FIRSTDATAKEY(opaque);
			/* Don't invalidate binary search bounds */
		}
	}

	/*
	 * If we are doing a recheck then we should have found the tuple we are
	 * checking.  Otherwise there's something very wrong --- probably, the
	 * index is on a non-immutable expression.
	 */
	if (checkUnique == UNIQUE_CHECK_EXISTING && !found)
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("failed to re-find tuple within index \"%s\"",
						RelationGetRelationName(rel)),
				 errhint("This may be because of a non-immutable index expression."),
				 errtableconstraint(heapRel,
									RelationGetRelationName(rel))));

	if (nbuf != InvalidBuffer)
		_bt_relbuf(rel, nbuf);

	return InvalidTransactionId;
}
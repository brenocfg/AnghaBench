#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_25__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
struct TYPE_41__ {int anynullkeys; int nextkey; int pivotsearch; int keysz; int /*<<< orphan*/ * scantid; int /*<<< orphan*/  heapkeyspace; TYPE_1__* scankeys; } ;
struct TYPE_36__ {size_t itemIndex; TYPE_5__* items; int /*<<< orphan*/  buf; } ;
struct TYPE_40__ {int numberOfKeys; scalar_t__ currTuples; TYPE_25__ currPos; TYPE_1__* keyData; int /*<<< orphan*/  qual_ok; } ;
struct TYPE_39__ {scalar_t__ tupleOffset; int /*<<< orphan*/  heapTid; } ;
struct TYPE_38__ {scalar_t__ xs_itup; scalar_t__ xs_want_itup; int /*<<< orphan*/  xs_heaptid; int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/ * parallel_scan; int /*<<< orphan*/  opaque; TYPE_3__* indexRelation; } ;
struct TYPE_37__ {scalar_t__* rd_opcintype; int /*<<< orphan*/ * rd_opfamily; } ;
struct TYPE_35__ {int sk_attno; int sk_flags; int sk_strategy; scalar_t__ sk_subtype; scalar_t__ sk_collation; int /*<<< orphan*/  sk_argument; } ;
typedef  int StrategyNumber ;
typedef  TYPE_1__ ScanKeyData ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_3__* Relation ;
typedef  scalar_t__ RegProcedure ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_4__* IndexScanDesc ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  int /*<<< orphan*/  BTStack ;
typedef  TYPE_5__ BTScanPosItem ;
typedef  TYPE_6__* BTScanOpaque ;
typedef  TYPE_7__ BTScanInsertData ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  BTEqualStrategyNumber 132 
#define  BTGreaterEqualStrategyNumber 131 
#define  BTGreaterStrategyNumber 130 
#define  BTLessEqualStrategyNumber 129 
#define  BTLessStrategyNumber 128 
 int /*<<< orphan*/  BTORDER_PROC ; 
 int /*<<< orphan*/  BTScanPosInvalidate (TYPE_25__) ; 
 int /*<<< orphan*/  BTScanPosIsValid (TYPE_25__) ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int INDEX_MAX_KEYS ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidOid ; 
 int InvalidStrategy ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetNumberPrev (int /*<<< orphan*/ ) ; 
 scalar_t__ P_NONE ; 
 int /*<<< orphan*/  PredicateLockPage (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockRelation (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegProcedureIsValid (scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int SK_BT_DESC ; 
 int SK_BT_NULLS_FIRST ; 
 int SK_ISNULL ; 
 int SK_ROW_END ; 
 int SK_ROW_HEADER ; 
 int SK_ROW_MEMBER ; 
 int SK_SEARCHNOTNULL ; 
 scalar_t__ ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyEntryInitialize (TYPE_1__*,int,int,int,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyEntryInitializeWithInfo (TYPE_1__*,int,int,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_binsrch (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_drop_lock_and_maybe_pin (TYPE_4__*,TYPE_25__*) ; 
 int _bt_endpoint (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_freestack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_heapkeyspace (TYPE_3__*) ; 
 int /*<<< orphan*/  _bt_initialize_more_data (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_parallel_done (TYPE_4__*) ; 
 int /*<<< orphan*/  _bt_parallel_readpage (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int _bt_parallel_seize (TYPE_4__*,scalar_t__*) ; 
 int /*<<< orphan*/  _bt_preprocess_keys (TYPE_4__*) ; 
 int /*<<< orphan*/  _bt_readpage (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_search (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_steppage (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ get_opfamily_proc (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * index_getprocinfo (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pgstat_count_index_scan (TYPE_3__*) ; 

bool
_bt_first(IndexScanDesc scan, ScanDirection dir)
{
	Relation	rel = scan->indexRelation;
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	Buffer		buf;
	BTStack		stack;
	OffsetNumber offnum;
	StrategyNumber strat;
	bool		nextkey;
	bool		goback;
	BTScanInsertData inskey;
	ScanKey		startKeys[INDEX_MAX_KEYS];
	ScanKeyData notnullkeys[INDEX_MAX_KEYS];
	int			keysCount = 0;
	int			i;
	bool		status = true;
	StrategyNumber strat_total;
	BTScanPosItem *currItem;
	BlockNumber blkno;

	Assert(!BTScanPosIsValid(so->currPos));

	pgstat_count_index_scan(rel);

	/*
	 * Examine the scan keys and eliminate any redundant keys; also mark the
	 * keys that must be matched to continue the scan.
	 */
	_bt_preprocess_keys(scan);

	/*
	 * Quit now if _bt_preprocess_keys() discovered that the scan keys can
	 * never be satisfied (eg, x == 1 AND x > 2).
	 */
	if (!so->qual_ok)
		return false;

	/*
	 * For parallel scans, get the starting page from shared state. If the
	 * scan has not started, proceed to find out first leaf page in the usual
	 * way while keeping other participating processes waiting.  If the scan
	 * has already begun, use the page number from the shared structure.
	 */
	if (scan->parallel_scan != NULL)
	{
		status = _bt_parallel_seize(scan, &blkno);
		if (!status)
			return false;
		else if (blkno == P_NONE)
		{
			_bt_parallel_done(scan);
			return false;
		}
		else if (blkno != InvalidBlockNumber)
		{
			if (!_bt_parallel_readpage(scan, blkno, dir))
				return false;
			goto readcomplete;
		}
	}

	/*----------
	 * Examine the scan keys to discover where we need to start the scan.
	 *
	 * We want to identify the keys that can be used as starting boundaries;
	 * these are =, >, or >= keys for a forward scan or =, <, <= keys for
	 * a backwards scan.  We can use keys for multiple attributes so long as
	 * the prior attributes had only =, >= (resp. =, <=) keys.  Once we accept
	 * a > or < boundary or find an attribute with no boundary (which can be
	 * thought of as the same as "> -infinity"), we can't use keys for any
	 * attributes to its right, because it would break our simplistic notion
	 * of what initial positioning strategy to use.
	 *
	 * When the scan keys include cross-type operators, _bt_preprocess_keys
	 * may not be able to eliminate redundant keys; in such cases we will
	 * arbitrarily pick a usable one for each attribute.  This is correct
	 * but possibly not optimal behavior.  (For example, with keys like
	 * "x >= 4 AND x >= 5" we would elect to scan starting at x=4 when
	 * x=5 would be more efficient.)  Since the situation only arises given
	 * a poorly-worded query plus an incomplete opfamily, live with it.
	 *
	 * When both equality and inequality keys appear for a single attribute
	 * (again, only possible when cross-type operators appear), we *must*
	 * select one of the equality keys for the starting point, because
	 * _bt_checkkeys() will stop the scan as soon as an equality qual fails.
	 * For example, if we have keys like "x >= 4 AND x = 10" and we elect to
	 * start at x=4, we will fail and stop before reaching x=10.  If multiple
	 * equality quals survive preprocessing, however, it doesn't matter which
	 * one we use --- by definition, they are either redundant or
	 * contradictory.
	 *
	 * Any regular (not SK_SEARCHNULL) key implies a NOT NULL qualifier.
	 * If the index stores nulls at the end of the index we'll be starting
	 * from, and we have no boundary key for the column (which means the key
	 * we deduced NOT NULL from is an inequality key that constrains the other
	 * end of the index), then we cons up an explicit SK_SEARCHNOTNULL key to
	 * use as a boundary key.  If we didn't do this, we might find ourselves
	 * traversing a lot of null entries at the start of the scan.
	 *
	 * In this loop, row-comparison keys are treated the same as keys on their
	 * first (leftmost) columns.  We'll add on lower-order columns of the row
	 * comparison below, if possible.
	 *
	 * The selected scan keys (at most one per index column) are remembered by
	 * storing their addresses into the local startKeys[] array.
	 *----------
	 */
	strat_total = BTEqualStrategyNumber;
	if (so->numberOfKeys > 0)
	{
		AttrNumber	curattr;
		ScanKey		chosen;
		ScanKey		impliesNN;
		ScanKey		cur;

		/*
		 * chosen is the so-far-chosen key for the current attribute, if any.
		 * We don't cast the decision in stone until we reach keys for the
		 * next attribute.
		 */
		curattr = 1;
		chosen = NULL;
		/* Also remember any scankey that implies a NOT NULL constraint */
		impliesNN = NULL;

		/*
		 * Loop iterates from 0 to numberOfKeys inclusive; we use the last
		 * pass to handle after-last-key processing.  Actual exit from the
		 * loop is at one of the "break" statements below.
		 */
		for (cur = so->keyData, i = 0;; cur++, i++)
		{
			if (i >= so->numberOfKeys || cur->sk_attno != curattr)
			{
				/*
				 * Done looking at keys for curattr.  If we didn't find a
				 * usable boundary key, see if we can deduce a NOT NULL key.
				 */
				if (chosen == NULL && impliesNN != NULL &&
					((impliesNN->sk_flags & SK_BT_NULLS_FIRST) ?
					 ScanDirectionIsForward(dir) :
					 ScanDirectionIsBackward(dir)))
				{
					/* Yes, so build the key in notnullkeys[keysCount] */
					chosen = &notnullkeys[keysCount];
					ScanKeyEntryInitialize(chosen,
										   (SK_SEARCHNOTNULL | SK_ISNULL |
											(impliesNN->sk_flags &
											 (SK_BT_DESC | SK_BT_NULLS_FIRST))),
										   curattr,
										   ((impliesNN->sk_flags & SK_BT_NULLS_FIRST) ?
											BTGreaterStrategyNumber :
											BTLessStrategyNumber),
										   InvalidOid,
										   InvalidOid,
										   InvalidOid,
										   (Datum) 0);
				}

				/*
				 * If we still didn't find a usable boundary key, quit; else
				 * save the boundary key pointer in startKeys.
				 */
				if (chosen == NULL)
					break;
				startKeys[keysCount++] = chosen;

				/*
				 * Adjust strat_total, and quit if we have stored a > or <
				 * key.
				 */
				strat = chosen->sk_strategy;
				if (strat != BTEqualStrategyNumber)
				{
					strat_total = strat;
					if (strat == BTGreaterStrategyNumber ||
						strat == BTLessStrategyNumber)
						break;
				}

				/*
				 * Done if that was the last attribute, or if next key is not
				 * in sequence (implying no boundary key is available for the
				 * next attribute).
				 */
				if (i >= so->numberOfKeys ||
					cur->sk_attno != curattr + 1)
					break;

				/*
				 * Reset for next attr.
				 */
				curattr = cur->sk_attno;
				chosen = NULL;
				impliesNN = NULL;
			}

			/*
			 * Can we use this key as a starting boundary for this attr?
			 *
			 * If not, does it imply a NOT NULL constraint?  (Because
			 * SK_SEARCHNULL keys are always assigned BTEqualStrategyNumber,
			 * *any* inequality key works for that; we need not test.)
			 */
			switch (cur->sk_strategy)
			{
				case BTLessStrategyNumber:
				case BTLessEqualStrategyNumber:
					if (chosen == NULL)
					{
						if (ScanDirectionIsBackward(dir))
							chosen = cur;
						else
							impliesNN = cur;
					}
					break;
				case BTEqualStrategyNumber:
					/* override any non-equality choice */
					chosen = cur;
					break;
				case BTGreaterEqualStrategyNumber:
				case BTGreaterStrategyNumber:
					if (chosen == NULL)
					{
						if (ScanDirectionIsForward(dir))
							chosen = cur;
						else
							impliesNN = cur;
					}
					break;
			}
		}
	}

	/*
	 * If we found no usable boundary keys, we have to start from one end of
	 * the tree.  Walk down that edge to the first or last key, and scan from
	 * there.
	 */
	if (keysCount == 0)
	{
		bool		match;

		match = _bt_endpoint(scan, dir);

		if (!match)
		{
			/* No match, so mark (parallel) scan finished */
			_bt_parallel_done(scan);
		}

		return match;
	}

	/*
	 * We want to start the scan somewhere within the index.  Set up an
	 * insertion scankey we can use to search for the boundary point we
	 * identified above.  The insertion scankey is built using the keys
	 * identified by startKeys[].  (Remaining insertion scankey fields are
	 * initialized after initial-positioning strategy is finalized.)
	 */
	Assert(keysCount <= INDEX_MAX_KEYS);
	for (i = 0; i < keysCount; i++)
	{
		ScanKey		cur = startKeys[i];

		Assert(cur->sk_attno == i + 1);

		if (cur->sk_flags & SK_ROW_HEADER)
		{
			/*
			 * Row comparison header: look to the first row member instead.
			 *
			 * The member scankeys are already in insertion format (ie, they
			 * have sk_func = 3-way-comparison function), but we have to watch
			 * out for nulls, which _bt_preprocess_keys didn't check. A null
			 * in the first row member makes the condition unmatchable, just
			 * like qual_ok = false.
			 */
			ScanKey		subkey = (ScanKey) DatumGetPointer(cur->sk_argument);

			Assert(subkey->sk_flags & SK_ROW_MEMBER);
			if (subkey->sk_flags & SK_ISNULL)
			{
				_bt_parallel_done(scan);
				return false;
			}
			memcpy(inskey.scankeys + i, subkey, sizeof(ScanKeyData));

			/*
			 * If the row comparison is the last positioning key we accepted,
			 * try to add additional keys from the lower-order row members.
			 * (If we accepted independent conditions on additional index
			 * columns, we use those instead --- doesn't seem worth trying to
			 * determine which is more restrictive.)  Note that this is OK
			 * even if the row comparison is of ">" or "<" type, because the
			 * condition applied to all but the last row member is effectively
			 * ">=" or "<=", and so the extra keys don't break the positioning
			 * scheme.  But, by the same token, if we aren't able to use all
			 * the row members, then the part of the row comparison that we
			 * did use has to be treated as just a ">=" or "<=" condition, and
			 * so we'd better adjust strat_total accordingly.
			 */
			if (i == keysCount - 1)
			{
				bool		used_all_subkeys = false;

				Assert(!(subkey->sk_flags & SK_ROW_END));
				for (;;)
				{
					subkey++;
					Assert(subkey->sk_flags & SK_ROW_MEMBER);
					if (subkey->sk_attno != keysCount + 1)
						break;	/* out-of-sequence, can't use it */
					if (subkey->sk_strategy != cur->sk_strategy)
						break;	/* wrong direction, can't use it */
					if (subkey->sk_flags & SK_ISNULL)
						break;	/* can't use null keys */
					Assert(keysCount < INDEX_MAX_KEYS);
					memcpy(inskey.scankeys + keysCount, subkey,
						   sizeof(ScanKeyData));
					keysCount++;
					if (subkey->sk_flags & SK_ROW_END)
					{
						used_all_subkeys = true;
						break;
					}
				}
				if (!used_all_subkeys)
				{
					switch (strat_total)
					{
						case BTLessStrategyNumber:
							strat_total = BTLessEqualStrategyNumber;
							break;
						case BTGreaterStrategyNumber:
							strat_total = BTGreaterEqualStrategyNumber;
							break;
					}
				}
				break;			/* done with outer loop */
			}
		}
		else
		{
			/*
			 * Ordinary comparison key.  Transform the search-style scan key
			 * to an insertion scan key by replacing the sk_func with the
			 * appropriate btree comparison function.
			 *
			 * If scankey operator is not a cross-type comparison, we can use
			 * the cached comparison function; otherwise gotta look it up in
			 * the catalogs.  (That can't lead to infinite recursion, since no
			 * indexscan initiated by syscache lookup will use cross-data-type
			 * operators.)
			 *
			 * We support the convention that sk_subtype == InvalidOid means
			 * the opclass input type; this is a hack to simplify life for
			 * ScanKeyInit().
			 */
			if (cur->sk_subtype == rel->rd_opcintype[i] ||
				cur->sk_subtype == InvalidOid)
			{
				FmgrInfo   *procinfo;

				procinfo = index_getprocinfo(rel, cur->sk_attno, BTORDER_PROC);
				ScanKeyEntryInitializeWithInfo(inskey.scankeys + i,
											   cur->sk_flags,
											   cur->sk_attno,
											   InvalidStrategy,
											   cur->sk_subtype,
											   cur->sk_collation,
											   procinfo,
											   cur->sk_argument);
			}
			else
			{
				RegProcedure cmp_proc;

				cmp_proc = get_opfamily_proc(rel->rd_opfamily[i],
											 rel->rd_opcintype[i],
											 cur->sk_subtype,
											 BTORDER_PROC);
				if (!RegProcedureIsValid(cmp_proc))
					elog(ERROR, "missing support function %d(%u,%u) for attribute %d of index \"%s\"",
						 BTORDER_PROC, rel->rd_opcintype[i], cur->sk_subtype,
						 cur->sk_attno, RelationGetRelationName(rel));
				ScanKeyEntryInitialize(inskey.scankeys + i,
									   cur->sk_flags,
									   cur->sk_attno,
									   InvalidStrategy,
									   cur->sk_subtype,
									   cur->sk_collation,
									   cmp_proc,
									   cur->sk_argument);
			}
		}
	}

	/*----------
	 * Examine the selected initial-positioning strategy to determine exactly
	 * where we need to start the scan, and set flag variables to control the
	 * code below.
	 *
	 * If nextkey = false, _bt_search and _bt_binsrch will locate the first
	 * item >= scan key.  If nextkey = true, they will locate the first
	 * item > scan key.
	 *
	 * If goback = true, we will then step back one item, while if
	 * goback = false, we will start the scan on the located item.
	 *----------
	 */
	switch (strat_total)
	{
		case BTLessStrategyNumber:

			/*
			 * Find first item >= scankey, then back up one to arrive at last
			 * item < scankey.  (Note: this positioning strategy is only used
			 * for a backward scan, so that is always the correct starting
			 * position.)
			 */
			nextkey = false;
			goback = true;
			break;

		case BTLessEqualStrategyNumber:

			/*
			 * Find first item > scankey, then back up one to arrive at last
			 * item <= scankey.  (Note: this positioning strategy is only used
			 * for a backward scan, so that is always the correct starting
			 * position.)
			 */
			nextkey = true;
			goback = true;
			break;

		case BTEqualStrategyNumber:

			/*
			 * If a backward scan was specified, need to start with last equal
			 * item not first one.
			 */
			if (ScanDirectionIsBackward(dir))
			{
				/*
				 * This is the same as the <= strategy.  We will check at the
				 * end whether the found item is actually =.
				 */
				nextkey = true;
				goback = true;
			}
			else
			{
				/*
				 * This is the same as the >= strategy.  We will check at the
				 * end whether the found item is actually =.
				 */
				nextkey = false;
				goback = false;
			}
			break;

		case BTGreaterEqualStrategyNumber:

			/*
			 * Find first item >= scankey.  (This is only used for forward
			 * scans.)
			 */
			nextkey = false;
			goback = false;
			break;

		case BTGreaterStrategyNumber:

			/*
			 * Find first item > scankey.  (This is only used for forward
			 * scans.)
			 */
			nextkey = true;
			goback = false;
			break;

		default:
			/* can't get here, but keep compiler quiet */
			elog(ERROR, "unrecognized strat_total: %d", (int) strat_total);
			return false;
	}

	/* Initialize remaining insertion scan key fields */
	inskey.heapkeyspace = _bt_heapkeyspace(rel);
	inskey.anynullkeys = false; /* unused */
	inskey.nextkey = nextkey;
	inskey.pivotsearch = false;
	inskey.scantid = NULL;
	inskey.keysz = keysCount;

	/*
	 * Use the manufactured insertion scan key to descend the tree and
	 * position ourselves on the target leaf page.
	 */
	stack = _bt_search(rel, &inskey, &buf, BT_READ, scan->xs_snapshot);

	/* don't need to keep the stack around... */
	_bt_freestack(stack);

	if (!BufferIsValid(buf))
	{
		/*
		 * We only get here if the index is completely empty. Lock relation
		 * because nothing finer to lock exists.
		 */
		PredicateLockRelation(rel, scan->xs_snapshot);

		/*
		 * mark parallel scan as done, so that all the workers can finish
		 * their scan
		 */
		_bt_parallel_done(scan);
		BTScanPosInvalidate(so->currPos);

		return false;
	}
	else
		PredicateLockPage(rel, BufferGetBlockNumber(buf),
						  scan->xs_snapshot);

	_bt_initialize_more_data(so, dir);

	/* position to the precise item on the page */
	offnum = _bt_binsrch(rel, &inskey, buf);

	/*
	 * If nextkey = false, we are positioned at the first item >= scan key, or
	 * possibly at the end of a page on which all the existing items are less
	 * than the scan key and we know that everything on later pages is greater
	 * than or equal to scan key.
	 *
	 * If nextkey = true, we are positioned at the first item > scan key, or
	 * possibly at the end of a page on which all the existing items are less
	 * than or equal to the scan key and we know that everything on later
	 * pages is greater than scan key.
	 *
	 * The actually desired starting point is either this item or the prior
	 * one, or in the end-of-page case it's the first item on the next page or
	 * the last item on this page.  Adjust the starting offset if needed. (If
	 * this results in an offset before the first item or after the last one,
	 * _bt_readpage will report no items found, and then we'll step to the
	 * next page as needed.)
	 */
	if (goback)
		offnum = OffsetNumberPrev(offnum);

	/* remember which buffer we have pinned, if any */
	Assert(!BTScanPosIsValid(so->currPos));
	so->currPos.buf = buf;

	/*
	 * Now load data from the first page of the scan.
	 */
	if (!_bt_readpage(scan, dir, offnum))
	{
		/*
		 * There's no actually-matching data on this page.  Try to advance to
		 * the next page.  Return false if there's no matching data at all.
		 */
		LockBuffer(so->currPos.buf, BUFFER_LOCK_UNLOCK);
		if (!_bt_steppage(scan, dir))
			return false;
	}
	else
	{
		/* Drop the lock, and maybe the pin, on the current page */
		_bt_drop_lock_and_maybe_pin(scan, &so->currPos);
	}

readcomplete:
	/* OK, itemIndex says what to return */
	currItem = &so->currPos.items[so->currPos.itemIndex];
	scan->xs_heaptid = currItem->heapTid;
	if (scan->xs_want_itup)
		scan->xs_itup = (IndexTuple) (so->currTuples + currItem->tupleOffset);

	return true;
}
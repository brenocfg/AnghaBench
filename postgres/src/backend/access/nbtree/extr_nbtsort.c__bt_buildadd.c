#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {void* btpo_next; void* btpo_prev; } ;
struct TYPE_29__ {scalar_t__ btps_lastoff; scalar_t__ btps_level; scalar_t__ btps_full; void* btps_blkno; scalar_t__ btps_page; TYPE_2__* btps_lowkey; struct TYPE_29__* btps_next; } ;
struct TYPE_28__ {int /*<<< orphan*/  index; int /*<<< orphan*/  inskey; int /*<<< orphan*/  btws_pages_alloced; int /*<<< orphan*/  heap; } ;
struct TYPE_27__ {int t_info; } ;
struct TYPE_26__ {int pd_lower; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/ * ItemId ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  IndexTupleData ;
typedef  TYPE_2__* IndexTuple ;
typedef  void* BlockNumber ;
typedef  TYPE_3__ BTWriteState ;
typedef  TYPE_4__ BTPageState ;
typedef  TYPE_5__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BTMaxItemSize (scalar_t__) ; 
 int /*<<< orphan*/  BTreeInnerTupleSetDownLink (TYPE_2__*,void*) ; 
 scalar_t__ BTreeTupleGetNAtts (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTreeTupleSetNAtts (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 TYPE_2__* CopyIndexTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 scalar_t__ IndexTupleSize (TYPE_2__*) ; 
 scalar_t__ ItemIdGetLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemIdSetUnused (int /*<<< orphan*/ *) ; 
 scalar_t__ MAXALIGN (int) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ OffsetNumberPrev (scalar_t__) ; 
 scalar_t__ P_FIRSTKEY ; 
 scalar_t__ P_HIKEY ; 
 scalar_t__ P_LEFTMOST (TYPE_5__*) ; 
 void* P_NONE ; 
 scalar_t__ PageGetFreeSpace (scalar_t__) ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PageGetItemId (scalar_t__,scalar_t__) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  PageIndexTupleOverwrite (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ _bt_blnewpage (scalar_t__) ; 
 int /*<<< orphan*/  _bt_blwritepage (TYPE_3__*,scalar_t__,void*) ; 
 int /*<<< orphan*/  _bt_check_third_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,TYPE_2__*) ; 
 TYPE_4__* _bt_pagestate (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  _bt_sortaddtup (scalar_t__,scalar_t__,TYPE_2__*,scalar_t__) ; 
 TYPE_2__* _bt_truncate (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
_bt_buildadd(BTWriteState *wstate, BTPageState *state, IndexTuple itup)
{
	Page		npage;
	BlockNumber nblkno;
	OffsetNumber last_off;
	Size		pgspc;
	Size		itupsz;
	bool		isleaf;

	/*
	 * This is a handy place to check for cancel interrupts during the btree
	 * load phase of index creation.
	 */
	CHECK_FOR_INTERRUPTS();

	npage = state->btps_page;
	nblkno = state->btps_blkno;
	last_off = state->btps_lastoff;

	pgspc = PageGetFreeSpace(npage);
	itupsz = IndexTupleSize(itup);
	itupsz = MAXALIGN(itupsz);
	/* Leaf case has slightly different rules due to suffix truncation */
	isleaf = (state->btps_level == 0);

	/*
	 * Check whether the new item can fit on a btree page on current level at
	 * all.
	 *
	 * Every newly built index will treat heap TID as part of the keyspace,
	 * which imposes the requirement that new high keys must occasionally have
	 * a heap TID appended within _bt_truncate().  That may leave a new pivot
	 * tuple one or two MAXALIGN() quantums larger than the original first
	 * right tuple it's derived from.  v4 deals with the problem by decreasing
	 * the limit on the size of tuples inserted on the leaf level by the same
	 * small amount.  Enforce the new v4+ limit on the leaf level, and the old
	 * limit on internal levels, since pivot tuples may need to make use of
	 * the reserved space.  This should never fail on internal pages.
	 */
	if (unlikely(itupsz > BTMaxItemSize(npage)))
		_bt_check_third_page(wstate->index, wstate->heap, isleaf, npage,
							 itup);

	/*
	 * Check to see if current page will fit new item, with space left over to
	 * append a heap TID during suffix truncation when page is a leaf page.
	 *
	 * It is guaranteed that we can fit at least 2 non-pivot tuples plus a
	 * high key with heap TID when finishing off a leaf page, since we rely on
	 * _bt_check_third_page() rejecting oversized non-pivot tuples.  On
	 * internal pages we can always fit 3 pivot tuples with larger internal
	 * page tuple limit (includes page high key).
	 *
	 * Most of the time, a page is only "full" in the sense that the soft
	 * fillfactor-wise limit has been exceeded.  However, we must always leave
	 * at least two items plus a high key on each page before starting a new
	 * page.  Disregard fillfactor and insert on "full" current page if we
	 * don't have the minimum number of items yet.  (Note that we deliberately
	 * assume that suffix truncation neither enlarges nor shrinks new high key
	 * when applying soft limit.)
	 */
	if (pgspc < itupsz + (isleaf ? MAXALIGN(sizeof(ItemPointerData)) : 0) ||
		(pgspc < state->btps_full && last_off > P_FIRSTKEY))
	{
		/*
		 * Finish off the page and write it out.
		 */
		Page		opage = npage;
		BlockNumber oblkno = nblkno;
		ItemId		ii;
		ItemId		hii;
		IndexTuple	oitup;

		/* Create new page of same level */
		npage = _bt_blnewpage(state->btps_level);

		/* and assign it a page position */
		nblkno = wstate->btws_pages_alloced++;

		/*
		 * We copy the last item on the page into the new page, and then
		 * rearrange the old page so that the 'last item' becomes its high key
		 * rather than a true data item.  There had better be at least two
		 * items on the page already, else the page would be empty of useful
		 * data.
		 */
		Assert(last_off > P_FIRSTKEY);
		ii = PageGetItemId(opage, last_off);
		oitup = (IndexTuple) PageGetItem(opage, ii);
		_bt_sortaddtup(npage, ItemIdGetLength(ii), oitup, P_FIRSTKEY);

		/*
		 * Move 'last' into the high key position on opage.  _bt_blnewpage()
		 * allocated empty space for a line pointer when opage was first
		 * created, so this is a matter of rearranging already-allocated space
		 * on page, and initializing high key line pointer. (Actually, leaf
		 * pages must also swap oitup with a truncated version of oitup, which
		 * is sometimes larger than oitup, though never by more than the space
		 * needed to append a heap TID.)
		 */
		hii = PageGetItemId(opage, P_HIKEY);
		*hii = *ii;
		ItemIdSetUnused(ii);	/* redundant */
		((PageHeader) opage)->pd_lower -= sizeof(ItemIdData);

		if (isleaf)
		{
			IndexTuple	lastleft;
			IndexTuple	truncated;

			/*
			 * Truncate away any unneeded attributes from high key on leaf
			 * level.  This is only done at the leaf level because downlinks
			 * in internal pages are either negative infinity items, or get
			 * their contents from copying from one level down.  See also:
			 * _bt_split().
			 *
			 * We don't try to bias our choice of split point to make it more
			 * likely that _bt_truncate() can truncate away more attributes,
			 * whereas the split point used within _bt_split() is chosen much
			 * more delicately.  Suffix truncation is mostly useful because it
			 * improves space utilization for workloads with random
			 * insertions.  It doesn't seem worthwhile to add logic for
			 * choosing a split point here for a benefit that is bound to be
			 * much smaller.
			 *
			 * Overwrite the old item with new truncated high key directly.
			 * oitup is already located at the physical beginning of tuple
			 * space, so this should directly reuse the existing tuple space.
			 */
			ii = PageGetItemId(opage, OffsetNumberPrev(last_off));
			lastleft = (IndexTuple) PageGetItem(opage, ii);

			truncated = _bt_truncate(wstate->index, lastleft, oitup,
									 wstate->inskey);
			if (!PageIndexTupleOverwrite(opage, P_HIKEY, (Item) truncated,
										 IndexTupleSize(truncated)))
				elog(ERROR, "failed to add high key to the index page");
			pfree(truncated);

			/* oitup should continue to point to the page's high key */
			hii = PageGetItemId(opage, P_HIKEY);
			oitup = (IndexTuple) PageGetItem(opage, hii);
		}

		/*
		 * Link the old page into its parent, using its low key.  If we don't
		 * have a parent, we have to create one; this adds a new btree level.
		 */
		if (state->btps_next == NULL)
			state->btps_next = _bt_pagestate(wstate, state->btps_level + 1);

		Assert((BTreeTupleGetNAtts(state->btps_lowkey, wstate->index) <=
				IndexRelationGetNumberOfKeyAttributes(wstate->index) &&
				BTreeTupleGetNAtts(state->btps_lowkey, wstate->index) > 0) ||
			   P_LEFTMOST((BTPageOpaque) PageGetSpecialPointer(opage)));
		Assert(BTreeTupleGetNAtts(state->btps_lowkey, wstate->index) == 0 ||
			   !P_LEFTMOST((BTPageOpaque) PageGetSpecialPointer(opage)));
		BTreeInnerTupleSetDownLink(state->btps_lowkey, oblkno);
		_bt_buildadd(wstate, state->btps_next, state->btps_lowkey);
		pfree(state->btps_lowkey);

		/*
		 * Save a copy of the high key from the old page.  It is also the low
		 * key for the new page.
		 */
		state->btps_lowkey = CopyIndexTuple(oitup);

		/*
		 * Set the sibling links for both pages.
		 */
		{
			BTPageOpaque oopaque = (BTPageOpaque) PageGetSpecialPointer(opage);
			BTPageOpaque nopaque = (BTPageOpaque) PageGetSpecialPointer(npage);

			oopaque->btpo_next = nblkno;
			nopaque->btpo_prev = oblkno;
			nopaque->btpo_next = P_NONE;	/* redundant */
		}

		/*
		 * Write out the old page.  We never need to touch it again, so we can
		 * free the opage workspace too.
		 */
		_bt_blwritepage(wstate, opage, oblkno);

		/*
		 * Reset last_off to point to new page
		 */
		last_off = P_FIRSTKEY;
	}

	/*
	 * By here, either original page is still the current page, or a new page
	 * was created that became the current page.  Either way, the current page
	 * definitely has space for new item.
	 *
	 * If the new item is the first for its page, it must also be the first
	 * item on its entire level.  On later same-level pages, a low key for a
	 * page will be copied from the prior page in the code above.  Generate a
	 * minus infinity low key here instead.
	 */
	if (last_off == P_HIKEY)
	{
		Assert(state->btps_lowkey == NULL);
		state->btps_lowkey = palloc0(sizeof(IndexTupleData));
		state->btps_lowkey->t_info = sizeof(IndexTupleData);
		BTreeTupleSetNAtts(state->btps_lowkey, 0);
	}

	/*
	 * Add the new item into the current page.
	 */
	last_off = OffsetNumberNext(last_off);
	_bt_sortaddtup(npage, itupsz, itup, last_off);

	state->btps_page = npage;
	state->btps_blkno = nblkno;
	state->btps_lastoff = last_off;
}
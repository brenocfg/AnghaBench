#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int bounds_valid; int /*<<< orphan*/  buf; TYPE_2__* itup_key; int /*<<< orphan*/  itemsz; int /*<<< orphan*/  itup; } ;
struct TYPE_11__ {int /*<<< orphan*/ * scantid; scalar_t__ heapkeyspace; } ;
struct TYPE_10__ {int /*<<< orphan*/  rel; scalar_t__ rootdescend; scalar_t__ readonly; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_1__ BtreeCheckState ;
typedef  int /*<<< orphan*/  BTStack ;
typedef  TYPE_2__* BTScanInsert ;
typedef  TYPE_3__ BTInsertStateData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexTupleSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_binsrch_insert (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ _bt_compare (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _bt_freestack (int /*<<< orphan*/ ) ; 
 TYPE_2__* _bt_mkscankey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_search (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static bool
bt_rootdescend(BtreeCheckState *state, IndexTuple itup)
{
	BTScanInsert key;
	BTStack		stack;
	Buffer		lbuf;
	bool		exists;

	key = _bt_mkscankey(state->rel, itup);
	Assert(key->heapkeyspace && key->scantid != NULL);

	/*
	 * Search from root.
	 *
	 * Ideally, we would arrange to only move right within _bt_search() when
	 * an interrupted page split is detected (i.e. when the incomplete split
	 * bit is found to be set), but for now we accept the possibility that
	 * that could conceal an inconsistency.
	 */
	Assert(state->readonly && state->rootdescend);
	exists = false;
	stack = _bt_search(state->rel, key, &lbuf, BT_READ, NULL);

	if (BufferIsValid(lbuf))
	{
		BTInsertStateData insertstate;
		OffsetNumber offnum;
		Page		page;

		insertstate.itup = itup;
		insertstate.itemsz = MAXALIGN(IndexTupleSize(itup));
		insertstate.itup_key = key;
		insertstate.bounds_valid = false;
		insertstate.buf = lbuf;

		/* Get matching tuple on leaf page */
		offnum = _bt_binsrch_insert(state->rel, &insertstate);
		/* Compare first >= matching item on leaf page, if any */
		page = BufferGetPage(lbuf);
		if (offnum <= PageGetMaxOffsetNumber(page) &&
			_bt_compare(state->rel, key, page, offnum) == 0)
			exists = true;
		_bt_relbuf(state->rel, lbuf);
	}

	_bt_freestack(stack);
	pfree(key);

	return exists;
}
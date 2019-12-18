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
typedef  int int32 ;
struct TYPE_9__ {int /*<<< orphan*/  btpo_next; } ;
struct TYPE_8__ {scalar_t__ nextkey; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  BTStack ;
typedef  TYPE_1__* BTScanInsert ;
typedef  TYPE_2__* BTPageOpaque ;

/* Variables and functions */
 int BT_READ ; 
 int /*<<< orphan*/  BT_WRITE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_HIKEY ; 
 scalar_t__ P_IGNORE (TYPE_2__*) ; 
 scalar_t__ P_INCOMPLETE_SPLIT (TYPE_2__*) ; 
 scalar_t__ P_RIGHTMOST (TYPE_2__*) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _bt_compare (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_finish_split (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _bt_relandgetbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

Buffer
_bt_moveright(Relation rel,
			  BTScanInsert key,
			  Buffer buf,
			  bool forupdate,
			  BTStack stack,
			  int access,
			  Snapshot snapshot)
{
	Page		page;
	BTPageOpaque opaque;
	int32		cmpval;

	/*
	 * When nextkey = false (normal case): if the scan key that brought us to
	 * this page is > the high key stored on the page, then the page has split
	 * and we need to move right.  (pg_upgrade'd !heapkeyspace indexes could
	 * have some duplicates to the right as well as the left, but that's
	 * something that's only ever dealt with on the leaf level, after
	 * _bt_search has found an initial leaf page.)
	 *
	 * When nextkey = true: move right if the scan key is >= page's high key.
	 * (Note that key.scantid cannot be set in this case.)
	 *
	 * The page could even have split more than once, so scan as far as
	 * needed.
	 *
	 * We also have to move right if we followed a link that brought us to a
	 * dead page.
	 */
	cmpval = key->nextkey ? 0 : 1;

	for (;;)
	{
		page = BufferGetPage(buf);
		TestForOldSnapshot(snapshot, rel, page);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);

		if (P_RIGHTMOST(opaque))
			break;

		/*
		 * Finish any incomplete splits we encounter along the way.
		 */
		if (forupdate && P_INCOMPLETE_SPLIT(opaque))
		{
			BlockNumber blkno = BufferGetBlockNumber(buf);

			/* upgrade our lock if necessary */
			if (access == BT_READ)
			{
				LockBuffer(buf, BUFFER_LOCK_UNLOCK);
				LockBuffer(buf, BT_WRITE);
			}

			if (P_INCOMPLETE_SPLIT(opaque))
				_bt_finish_split(rel, buf, stack);
			else
				_bt_relbuf(rel, buf);

			/* re-acquire the lock in the right mode, and re-check */
			buf = _bt_getbuf(rel, blkno, access);
			continue;
		}

		if (P_IGNORE(opaque) || _bt_compare(rel, key, page, P_HIKEY) >= cmpval)
		{
			/* step right one page */
			buf = _bt_relandgetbuf(rel, buf, opaque->btpo_next, access);
			continue;
		}
		else
			break;
	}

	if (P_IGNORE(opaque))
		elog(ERROR, "fell off the end of index \"%s\"",
			 RelationGetRelationName(rel));

	return buf;
}
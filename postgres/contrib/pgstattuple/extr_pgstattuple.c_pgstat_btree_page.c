#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  free_space; } ;
typedef  TYPE_1__ pgstattuple_type ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  scalar_t__ BTPageOpaque ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  P_FIRSTDATAKEY (scalar_t__) ; 
 scalar_t__ P_IGNORE (scalar_t__) ; 
 scalar_t__ P_ISLEAF (scalar_t__) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_index_page (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgstat_btree_page(pgstattuple_type *stat, Relation rel, BlockNumber blkno,
				  BufferAccessStrategy bstrategy)
{
	Buffer		buf;
	Page		page;

	buf = ReadBufferExtended(rel, MAIN_FORKNUM, blkno, RBM_NORMAL, bstrategy);
	LockBuffer(buf, BT_READ);
	page = BufferGetPage(buf);

	/* Page is valid, see what to do with it */
	if (PageIsNew(page))
	{
		/* fully empty page */
		stat->free_space += BLCKSZ;
	}
	else
	{
		BTPageOpaque opaque;

		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		if (P_IGNORE(opaque))
		{
			/* recyclable page */
			stat->free_space += BLCKSZ;
		}
		else if (P_ISLEAF(opaque))
		{
			pgstat_index_page(stat, page, P_FIRSTDATAKEY(opaque),
							  PageGetMaxOffsetNumber(page));
		}
		else
		{
			/* root or node */
		}
	}

	_bt_relbuf(rel, buf);
}
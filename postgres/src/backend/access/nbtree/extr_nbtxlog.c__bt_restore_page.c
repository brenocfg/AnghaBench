#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ Item ;
typedef  int /*<<< orphan*/  IndexTupleData ;

/* Variables and functions */
 int /*<<< orphan*/  IndexTupleSize (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 int MaxIndexTuplesPerPage ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
_bt_restore_page(Page page, char *from, int len)
{
	IndexTupleData itupdata;
	Size		itemsz;
	char	   *end = from + len;
	Item		items[MaxIndexTuplesPerPage];
	uint16		itemsizes[MaxIndexTuplesPerPage];
	int			i;
	int			nitems;

	/*
	 * To get the items back in the original order, we add them to the page in
	 * reverse.  To figure out where one tuple ends and another begins, we
	 * have to scan them in forward order first.
	 */
	i = 0;
	while (from < end)
	{
		/*
		 * As we step through the items, 'from' won't always be properly
		 * aligned, so we need to use memcpy().  Further, we use Item (which
		 * is just a char*) here for our items array for the same reason;
		 * wouldn't want the compiler or anyone thinking that an item is
		 * aligned when it isn't.
		 */
		memcpy(&itupdata, from, sizeof(IndexTupleData));
		itemsz = IndexTupleSize(&itupdata);
		itemsz = MAXALIGN(itemsz);

		items[i] = (Item) from;
		itemsizes[i] = itemsz;
		i++;

		from += itemsz;
	}
	nitems = i;

	for (i = nitems - 1; i >= 0; i--)
	{
		if (PageAddItem(page, items[i], itemsizes[i], nitems - i,
						false, false) == InvalidOffsetNumber)
			elog(PANIC, "_bt_restore_page: cannot add item to page");
		from += itemsz;
	}
}
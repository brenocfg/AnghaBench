#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_2__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__* IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemPointerCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_compute_xid_horizon_for_tuples (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

TransactionId
index_compute_xid_horizon_for_tuples(Relation irel,
									 Relation hrel,
									 Buffer ibuf,
									 OffsetNumber *itemnos,
									 int nitems)
{
	ItemPointerData *ttids =
	(ItemPointerData *) palloc(sizeof(ItemPointerData) * nitems);
	TransactionId latestRemovedXid = InvalidTransactionId;
	Page		ipage = BufferGetPage(ibuf);
	IndexTuple	itup;

	/* identify what the index tuples about to be deleted point to */
	for (int i = 0; i < nitems; i++)
	{
		ItemId		iitemid;

		iitemid = PageGetItemId(ipage, itemnos[i]);
		itup = (IndexTuple) PageGetItem(ipage, iitemid);

		ItemPointerCopy(&itup->t_tid, &ttids[i]);
	}

	/* determine the actual xid horizon */
	latestRemovedXid =
		table_compute_xid_horizon_for_tuples(hrel, ttids, nitems);

	pfree(ttids);

	return latestRemovedXid;
}
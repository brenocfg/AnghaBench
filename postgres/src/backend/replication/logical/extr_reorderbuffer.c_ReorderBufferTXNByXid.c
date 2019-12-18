#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
struct TYPE_11__ {scalar_t__ by_txn_last_xid; TYPE_2__* by_txn_last_txn; int /*<<< orphan*/  toplevel_by_lsn; int /*<<< orphan*/  current_restart_decoding_lsn; int /*<<< orphan*/  by_txn; } ;
struct TYPE_10__ {int /*<<< orphan*/  node; int /*<<< orphan*/  restart_decoding_lsn; scalar_t__ first_lsn; scalar_t__ xid; } ;
struct TYPE_9__ {TYPE_2__* txn; } ;
typedef  TYPE_1__ ReorderBufferTXNByIdEnt ;
typedef  TYPE_2__ ReorderBufferTXN ;
typedef  TYPE_3__ ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertTXNLsnOrder (TYPE_3__*) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ InvalidXLogRecPtr ; 
 TYPE_2__* ReorderBufferGetTXN (TYPE_3__*) ; 
 int TransactionIdIsValid (scalar_t__) ; 
 int /*<<< orphan*/  dlist_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ReorderBufferTXN *
ReorderBufferTXNByXid(ReorderBuffer *rb, TransactionId xid, bool create,
					  bool *is_new, XLogRecPtr lsn, bool create_as_top)
{
	ReorderBufferTXN *txn;
	ReorderBufferTXNByIdEnt *ent;
	bool		found;

	Assert(TransactionIdIsValid(xid));

	/*
	 * Check the one-entry lookup cache first
	 */
	if (TransactionIdIsValid(rb->by_txn_last_xid) &&
		rb->by_txn_last_xid == xid)
	{
		txn = rb->by_txn_last_txn;

		if (txn != NULL)
		{
			/* found it, and it's valid */
			if (is_new)
				*is_new = false;
			return txn;
		}

		/*
		 * cached as non-existent, and asked not to create? Then nothing else
		 * to do.
		 */
		if (!create)
			return NULL;
		/* otherwise fall through to create it */
	}

	/*
	 * If the cache wasn't hit or it yielded an "does-not-exist" and we want
	 * to create an entry.
	 */

	/* search the lookup table */
	ent = (ReorderBufferTXNByIdEnt *)
		hash_search(rb->by_txn,
					(void *) &xid,
					create ? HASH_ENTER : HASH_FIND,
					&found);
	if (found)
		txn = ent->txn;
	else if (create)
	{
		/* initialize the new entry, if creation was requested */
		Assert(ent != NULL);
		Assert(lsn != InvalidXLogRecPtr);

		ent->txn = ReorderBufferGetTXN(rb);
		ent->txn->xid = xid;
		txn = ent->txn;
		txn->first_lsn = lsn;
		txn->restart_decoding_lsn = rb->current_restart_decoding_lsn;

		if (create_as_top)
		{
			dlist_push_tail(&rb->toplevel_by_lsn, &txn->node);
			AssertTXNLsnOrder(rb);
		}
	}
	else
		txn = NULL;				/* not found and not asked to create */

	/* update cache */
	rb->by_txn_last_xid = xid;
	rb->by_txn_last_txn = txn;

	if (is_new)
		*is_new = !found;

	Assert(!create || txn != NULL);
	return txn;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ by_txn_last_xid; int /*<<< orphan*/ * by_txn_last_txn; } ;
struct TYPE_6__ {scalar_t__ xid; struct TYPE_6__* invalidations; int /*<<< orphan*/ * tuplecid_hash; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  TYPE_2__ ReorderBuffer ;

/* Variables and functions */
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
ReorderBufferReturnTXN(ReorderBuffer *rb, ReorderBufferTXN *txn)
{
	/* clean the lookup cache if we were cached (quite likely) */
	if (rb->by_txn_last_xid == txn->xid)
	{
		rb->by_txn_last_xid = InvalidTransactionId;
		rb->by_txn_last_txn = NULL;
	}

	/* free data that's contained */

	if (txn->tuplecid_hash != NULL)
	{
		hash_destroy(txn->tuplecid_hash);
		txn->tuplecid_hash = NULL;
	}

	if (txn->invalidations)
	{
		pfree(txn->invalidations);
		txn->invalidations = NULL;
	}

	pfree(txn);
}
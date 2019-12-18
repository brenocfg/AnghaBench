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
struct TYPE_7__ {int atCommit; struct TYPE_7__* next; int /*<<< orphan*/  nestLevel; int /*<<< orphan*/  backend; int /*<<< orphan*/  relnode; } ;
struct TYPE_6__ {int /*<<< orphan*/  rd_backend; int /*<<< orphan*/  rd_node; } ;
typedef  TYPE_1__* Relation ;
typedef  TYPE_2__ PendingRelDelete ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTransactionNestLevel () ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RelationCloseSmgr (TYPE_1__*) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 TYPE_2__* pendingDeletes ; 

void
RelationDropStorage(Relation rel)
{
	PendingRelDelete *pending;

	/* Add the relation to the list of stuff to delete at commit */
	pending = (PendingRelDelete *)
		MemoryContextAlloc(TopMemoryContext, sizeof(PendingRelDelete));
	pending->relnode = rel->rd_node;
	pending->backend = rel->rd_backend;
	pending->atCommit = true;	/* delete if commit */
	pending->nestLevel = GetCurrentTransactionNestLevel();
	pending->next = pendingDeletes;
	pendingDeletes = pending;

	/*
	 * NOTE: if the relation was created in this transaction, it will now be
	 * present in the pending-delete list twice, once with atCommit true and
	 * once with atCommit false.  Hence, it will be physically deleted at end
	 * of xact in either case (and the other entry will be ignored by
	 * smgrDoPendingDeletes, so no error will occur).  We could instead remove
	 * the existing list entry and delete the physical file immediately, but
	 * for now I'll keep the logic simple.
	 */

	RelationCloseSmgr(rel);
}
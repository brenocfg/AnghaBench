#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_8__ {scalar_t__ strategy; } ;
struct TYPE_6__ {TYPE_5__* lefttree; scalar_t__ plan; int /*<<< orphan*/  ps_ResultTupleSlot; } ;
struct TYPE_7__ {int setop_done; int table_filled; TYPE_1__ ps; int /*<<< orphan*/  hashtable; scalar_t__ tableContext; int /*<<< orphan*/ * grp_firstTuple; int /*<<< orphan*/  hashiter; scalar_t__ numOutput; } ;
typedef  TYPE_2__ SetOpState ;
typedef  TYPE_3__ SetOp ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecReScan (TYPE_5__*) ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (scalar_t__) ; 
 int /*<<< orphan*/  ResetTupleHashIterator (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetTupleHashTable (int /*<<< orphan*/ ) ; 
 scalar_t__ SETOP_HASHED ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 

void
ExecReScanSetOp(SetOpState *node)
{
	ExecClearTuple(node->ps.ps_ResultTupleSlot);
	node->setop_done = false;
	node->numOutput = 0;

	if (((SetOp *) node->ps.plan)->strategy == SETOP_HASHED)
	{
		/*
		 * In the hashed case, if we haven't yet built the hash table then we
		 * can just return; nothing done yet, so nothing to undo. If subnode's
		 * chgParam is not NULL then it will be re-scanned by ExecProcNode,
		 * else no reason to re-scan it at all.
		 */
		if (!node->table_filled)
			return;

		/*
		 * If we do have the hash table and the subplan does not have any
		 * parameter changes, then we can just rescan the existing hash table;
		 * no need to build it again.
		 */
		if (node->ps.lefttree->chgParam == NULL)
		{
			ResetTupleHashIterator(node->hashtable, &node->hashiter);
			return;
		}
	}

	/* Release first tuple of group, if we have made a copy */
	if (node->grp_firstTuple != NULL)
	{
		heap_freetuple(node->grp_firstTuple);
		node->grp_firstTuple = NULL;
	}

	/* Release any hashtable storage */
	if (node->tableContext)
		MemoryContextResetAndDeleteChildren(node->tableContext);

	/* And rebuild empty hashtable if needed */
	if (((SetOp *) node->ps.plan)->strategy == SETOP_HASHED)
	{
		ResetTupleHashTable(node->hashtable);
		node->table_filled = false;
	}

	/*
	 * if chgParam of subnode is not null then plan will be re-scanned by
	 * first ExecProcNode.
	 */
	if (node->ps.lefttree->chgParam == NULL)
		ExecReScan(node->ps.lefttree);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numberOfKeys; int numberOfOrderBys; int xs_want_itup; int kill_prior_tuple; int ignore_killed_tuples; int /*<<< orphan*/ * xs_hitupdesc; int /*<<< orphan*/ * xs_hitup; int /*<<< orphan*/ * xs_itupdesc; int /*<<< orphan*/ * xs_itup; int /*<<< orphan*/ * opaque; int /*<<< orphan*/  xactStartedInRecovery; int /*<<< orphan*/ * orderByData; int /*<<< orphan*/ * keyData; int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/  indexRelation; int /*<<< orphan*/ * xs_heapfetch; int /*<<< orphan*/ * heapRelation; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  void* ScanKey ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexScanDescData ;
typedef  TYPE_1__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidSnapshot ; 
 int /*<<< orphan*/  TransactionStartedDuringRecovery () ; 
 scalar_t__ palloc (int) ; 

IndexScanDesc
RelationGetIndexScan(Relation indexRelation, int nkeys, int norderbys)
{
	IndexScanDesc scan;

	scan = (IndexScanDesc) palloc(sizeof(IndexScanDescData));

	scan->heapRelation = NULL;	/* may be set later */
	scan->xs_heapfetch = NULL;
	scan->indexRelation = indexRelation;
	scan->xs_snapshot = InvalidSnapshot;	/* caller must initialize this */
	scan->numberOfKeys = nkeys;
	scan->numberOfOrderBys = norderbys;

	/*
	 * We allocate key workspace here, but it won't get filled until amrescan.
	 */
	if (nkeys > 0)
		scan->keyData = (ScanKey) palloc(sizeof(ScanKeyData) * nkeys);
	else
		scan->keyData = NULL;
	if (norderbys > 0)
		scan->orderByData = (ScanKey) palloc(sizeof(ScanKeyData) * norderbys);
	else
		scan->orderByData = NULL;

	scan->xs_want_itup = false; /* may be set later */

	/*
	 * During recovery we ignore killed tuples and don't bother to kill them
	 * either. We do this because the xmin on the primary node could easily be
	 * later than the xmin on the standby node, so that what the primary
	 * thinks is killed is supposed to be visible on standby. So for correct
	 * MVCC for queries during recovery we must ignore these hints and check
	 * all tuples. Do *not* set ignore_killed_tuples to true when running in a
	 * transaction that was started during recovery. xactStartedInRecovery
	 * should not be altered by index AMs.
	 */
	scan->kill_prior_tuple = false;
	scan->xactStartedInRecovery = TransactionStartedDuringRecovery();
	scan->ignore_killed_tuples = !scan->xactStartedInRecovery;

	scan->opaque = NULL;

	scan->xs_itup = NULL;
	scan->xs_itupdesc = NULL;
	scan->xs_hitup = NULL;
	scan->xs_hitupdesc = NULL;

	return scan;
}
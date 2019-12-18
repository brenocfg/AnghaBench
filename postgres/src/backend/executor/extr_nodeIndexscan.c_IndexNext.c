#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_20__ {int /*<<< orphan*/  es_snapshot; int /*<<< orphan*/  es_direction; } ;
struct TYPE_19__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_18__ {int /*<<< orphan*/  indexorderdir; } ;
struct TYPE_17__ {scalar_t__ xs_recheck; } ;
struct TYPE_14__ {TYPE_6__* ps_ExprContext; scalar_t__ plan; TYPE_7__* state; } ;
struct TYPE_15__ {int /*<<< orphan*/  ss_currentRelation; int /*<<< orphan*/ * ss_ScanTupleSlot; TYPE_1__ ps; } ;
struct TYPE_16__ {scalar_t__ iss_NumRuntimeKeys; int iss_ReachedEnd; int /*<<< orphan*/  indexqualorig; int /*<<< orphan*/  iss_NumOrderByKeys; int /*<<< orphan*/  iss_OrderByKeys; int /*<<< orphan*/  iss_NumScanKeys; int /*<<< orphan*/  iss_ScanKeys; scalar_t__ iss_RuntimeKeysReady; TYPE_4__* iss_ScanDesc; int /*<<< orphan*/  iss_RelationDesc; TYPE_2__ ss; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_3__ IndexScanState ;
typedef  TYPE_4__* IndexScanDesc ;
typedef  TYPE_5__ IndexScan ;
typedef  TYPE_6__ ExprContext ;
typedef  TYPE_7__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  BackwardScanDirection ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/ * ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecQualAndReset (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  InstrCountFiltered2 (TYPE_3__*,int) ; 
 scalar_t__ ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 TYPE_4__* index_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ index_getnext_slot (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_rescan (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
IndexNext(IndexScanState *node)
{
	EState	   *estate;
	ExprContext *econtext;
	ScanDirection direction;
	IndexScanDesc scandesc;
	TupleTableSlot *slot;

	/*
	 * extract necessary information from index scan node
	 */
	estate = node->ss.ps.state;
	direction = estate->es_direction;
	/* flip direction if this is an overall backward scan */
	if (ScanDirectionIsBackward(((IndexScan *) node->ss.ps.plan)->indexorderdir))
	{
		if (ScanDirectionIsForward(direction))
			direction = BackwardScanDirection;
		else if (ScanDirectionIsBackward(direction))
			direction = ForwardScanDirection;
	}
	scandesc = node->iss_ScanDesc;
	econtext = node->ss.ps.ps_ExprContext;
	slot = node->ss.ss_ScanTupleSlot;

	if (scandesc == NULL)
	{
		/*
		 * We reach here if the index scan is not parallel, or if we're
		 * serially executing an index scan that was planned to be parallel.
		 */
		scandesc = index_beginscan(node->ss.ss_currentRelation,
								   node->iss_RelationDesc,
								   estate->es_snapshot,
								   node->iss_NumScanKeys,
								   node->iss_NumOrderByKeys);

		node->iss_ScanDesc = scandesc;

		/*
		 * If no run-time keys to calculate or they are ready, go ahead and
		 * pass the scankeys to the index AM.
		 */
		if (node->iss_NumRuntimeKeys == 0 || node->iss_RuntimeKeysReady)
			index_rescan(scandesc,
						 node->iss_ScanKeys, node->iss_NumScanKeys,
						 node->iss_OrderByKeys, node->iss_NumOrderByKeys);
	}

	/*
	 * ok, now that we have what we need, fetch the next tuple.
	 */
	while (index_getnext_slot(scandesc, direction, slot))
	{
		CHECK_FOR_INTERRUPTS();

		/*
		 * If the index was lossy, we have to recheck the index quals using
		 * the fetched tuple.
		 */
		if (scandesc->xs_recheck)
		{
			econtext->ecxt_scantuple = slot;
			if (!ExecQualAndReset(node->indexqualorig, econtext))
			{
				/* Fails recheck, so drop it and loop back for another */
				InstrCountFiltered2(node, 1);
				continue;
			}
		}

		return slot;
	}

	/*
	 * if we get here it means the index scan failed so we are at the end of
	 * the scan..
	 */
	node->iss_ReachedEnd = true;
	return ExecClearTuple(slot);
}
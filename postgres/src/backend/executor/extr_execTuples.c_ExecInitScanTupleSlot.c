#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlotOps ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_8__ {int /*<<< orphan*/  es_tupleTable; } ;
struct TYPE_6__ {int scanopsset; int /*<<< orphan*/  const* scanops; int /*<<< orphan*/  scanopsfixed; int /*<<< orphan*/ * scandesc; } ;
struct TYPE_7__ {TYPE_1__ ps; int /*<<< orphan*/  ss_ScanTupleSlot; } ;
typedef  TYPE_2__ ScanState ;
typedef  TYPE_3__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecAllocTableSlot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void
ExecInitScanTupleSlot(EState *estate, ScanState *scanstate,
					  TupleDesc tupledesc, const TupleTableSlotOps *tts_ops)
{
	scanstate->ss_ScanTupleSlot = ExecAllocTableSlot(&estate->es_tupleTable,
													 tupledesc, tts_ops);
	scanstate->ps.scandesc = tupledesc;
	scanstate->ps.scanopsfixed = tupledesc != NULL;
	scanstate->ps.scanops = tts_ops;
	scanstate->ps.scanopsset = true;
}
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
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int /*<<< orphan*/ * ss_ScanTupleSlot; } ;
typedef  TYPE_1__ ScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecSetSlotDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecAssignScanType(ScanState *scanstate, TupleDesc tupDesc)
{
	TupleTableSlot *slot = scanstate->ss_ScanTupleSlot;

	ExecSetSlotDescriptor(slot, tupDesc);
}
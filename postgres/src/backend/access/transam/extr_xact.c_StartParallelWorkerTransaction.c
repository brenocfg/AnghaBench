#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ blockState; int /*<<< orphan*/  fullTransactionId; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parallelCurrentXids; int /*<<< orphan*/  nParallelCurrentXids; int /*<<< orphan*/  currentCommandId; int /*<<< orphan*/  currentFullTransactionId; int /*<<< orphan*/  topFullTransactionId; int /*<<< orphan*/  xactDeferrable; int /*<<< orphan*/  xactIsoLevel; } ;
typedef  TYPE_1__ SerializedTransactionState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* CurrentTransactionState ; 
 int /*<<< orphan*/ * ParallelCurrentXids ; 
 int /*<<< orphan*/  StartTransaction () ; 
 scalar_t__ TBLOCK_DEFAULT ; 
 scalar_t__ TBLOCK_PARALLEL_INPROGRESS ; 
 int /*<<< orphan*/  XactDeferrable ; 
 int /*<<< orphan*/  XactIsoLevel ; 
 int /*<<< orphan*/  XactTopFullTransactionId ; 
 int /*<<< orphan*/  currentCommandId ; 
 int /*<<< orphan*/  nParallelCurrentXids ; 

void
StartParallelWorkerTransaction(char *tstatespace)
{
	SerializedTransactionState *tstate;

	Assert(CurrentTransactionState->blockState == TBLOCK_DEFAULT);
	StartTransaction();

	tstate = (SerializedTransactionState *) tstatespace;
	XactIsoLevel = tstate->xactIsoLevel;
	XactDeferrable = tstate->xactDeferrable;
	XactTopFullTransactionId = tstate->topFullTransactionId;
	CurrentTransactionState->fullTransactionId =
		tstate->currentFullTransactionId;
	currentCommandId = tstate->currentCommandId;
	nParallelCurrentXids = tstate->nParallelCurrentXids;
	ParallelCurrentXids = &tstate->parallelCurrentXids[0];

	CurrentTransactionState->blockState = TBLOCK_PARALLEL_INPROGRESS;
}
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
struct TYPE_2__ {scalar_t__ blockState; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CommitTransaction () ; 
 TYPE_1__* CurrentTransactionState ; 
 scalar_t__ TBLOCK_DEFAULT ; 
 scalar_t__ TBLOCK_PARALLEL_INPROGRESS ; 

void
EndParallelWorkerTransaction(void)
{
	Assert(CurrentTransactionState->blockState == TBLOCK_PARALLEL_INPROGRESS);
	CommitTransaction();
	CurrentTransactionState->blockState = TBLOCK_DEFAULT;
}
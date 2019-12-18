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
typedef  TYPE_1__* TransactionState ;
struct TYPE_3__ {scalar_t__ blockState; } ;

/* Variables and functions */
 TYPE_1__* CurrentTransactionState ; 
 scalar_t__ TBLOCK_IMPLICIT_INPROGRESS ; 
 scalar_t__ TBLOCK_STARTED ; 

void
EndImplicitTransactionBlock(void)
{
	TransactionState s = CurrentTransactionState;

	/*
	 * If we are in IMPLICIT_INPROGRESS state, switch back to STARTED state,
	 * allowing CommitTransactionCommand to commit whatever happened during
	 * the implicit transaction block as though it were a single statement.
	 *
	 * For caller convenience, we consider all other transaction states as
	 * legal here; otherwise the caller would need its own state check, which
	 * seems rather pointless.
	 */
	if (s->blockState == TBLOCK_IMPLICIT_INPROGRESS)
		s->blockState = TBLOCK_STARTED;
}
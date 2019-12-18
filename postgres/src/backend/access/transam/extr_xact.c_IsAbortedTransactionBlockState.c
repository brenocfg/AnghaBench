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
 scalar_t__ TBLOCK_ABORT ; 
 scalar_t__ TBLOCK_SUBABORT ; 

bool
IsAbortedTransactionBlockState(void)
{
	TransactionState s = CurrentTransactionState;

	if (s->blockState == TBLOCK_ABORT ||
		s->blockState == TBLOCK_SUBABORT)
		return true;

	return false;
}
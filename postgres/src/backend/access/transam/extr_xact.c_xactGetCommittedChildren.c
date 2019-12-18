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
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_3__ {scalar_t__ nChildXids; int /*<<< orphan*/ * childXids; } ;

/* Variables and functions */
 TYPE_1__* CurrentTransactionState ; 

int
xactGetCommittedChildren(TransactionId **ptr)
{
	TransactionState s = CurrentTransactionState;

	if (s->nChildXids == 0)
		*ptr = NULL;
	else
		*ptr = s->childXids;

	return s->nChildXids;
}
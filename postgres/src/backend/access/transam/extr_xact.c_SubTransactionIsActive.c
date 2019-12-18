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
struct TYPE_3__ {scalar_t__ state; scalar_t__ subTransactionId; struct TYPE_3__* parent; } ;
typedef  scalar_t__ SubTransactionId ;

/* Variables and functions */
 TYPE_1__* CurrentTransactionState ; 
 scalar_t__ TRANS_ABORT ; 

bool
SubTransactionIsActive(SubTransactionId subxid)
{
	TransactionState s;

	for (s = CurrentTransactionState; s != NULL; s = s->parent)
	{
		if (s->state == TRANS_ABORT)
			continue;
		if (s->subTransactionId == subxid)
			return true;
	}
	return false;
}
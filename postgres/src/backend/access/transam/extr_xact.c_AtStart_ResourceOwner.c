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
struct TYPE_3__ {int /*<<< orphan*/ * curTransactionOwner; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CurTransactionResourceOwner ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/ * ResourceOwnerCreate (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * TopTransactionResourceOwner ; 

__attribute__((used)) static void
AtStart_ResourceOwner(void)
{
	TransactionState s = CurrentTransactionState;

	/*
	 * We shouldn't have a transaction resource owner already.
	 */
	Assert(TopTransactionResourceOwner == NULL);

	/*
	 * Create a toplevel resource owner for the transaction.
	 */
	s->curTransactionOwner = ResourceOwnerCreate(NULL, "TopTransaction");

	TopTransactionResourceOwner = s->curTransactionOwner;
	CurTransactionResourceOwner = s->curTransactionOwner;
	CurrentResourceOwner = s->curTransactionOwner;
}
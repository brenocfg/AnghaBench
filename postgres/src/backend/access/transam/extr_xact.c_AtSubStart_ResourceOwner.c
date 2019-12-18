#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* TransactionState ;
struct TYPE_5__ {int /*<<< orphan*/  curTransactionOwner; TYPE_1__* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  curTransactionOwner; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurTransactionResourceOwner ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 TYPE_2__* CurrentTransactionState ; 
 int /*<<< orphan*/  ResourceOwnerCreate (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
AtSubStart_ResourceOwner(void)
{
	TransactionState s = CurrentTransactionState;

	Assert(s->parent != NULL);

	/*
	 * Create a resource owner for the subtransaction.  We make it a child of
	 * the immediate parent's resource owner.
	 */
	s->curTransactionOwner =
		ResourceOwnerCreate(s->parent->curTransactionOwner,
							"SubTransaction");

	CurTransactionResourceOwner = s->curTransactionOwner;
	CurrentResourceOwner = s->curTransactionOwner;
}
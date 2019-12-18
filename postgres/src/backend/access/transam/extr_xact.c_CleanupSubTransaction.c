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
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/ * curTransactionOwner; TYPE_1__* parent; int /*<<< orphan*/  subTransactionId; } ;
struct TYPE_4__ {int /*<<< orphan*/  curTransactionOwner; } ;

/* Variables and functions */
 int /*<<< orphan*/  AtSubCleanup_Memory () ; 
 int /*<<< orphan*/  AtSubCleanup_Portals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurTransactionResourceOwner ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 TYPE_2__* CurrentTransactionState ; 
 int /*<<< orphan*/  PopTransaction () ; 
 int /*<<< orphan*/  ResourceOwnerDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowTransactionState (char*) ; 
 scalar_t__ TRANS_ABORT ; 
 scalar_t__ TRANS_DEFAULT ; 
 int /*<<< orphan*/  TransStateAsString (scalar_t__) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CleanupSubTransaction(void)
{
	TransactionState s = CurrentTransactionState;

	ShowTransactionState("CleanupSubTransaction");

	if (s->state != TRANS_ABORT)
		elog(WARNING, "CleanupSubTransaction while in %s state",
			 TransStateAsString(s->state));

	AtSubCleanup_Portals(s->subTransactionId);

	CurrentResourceOwner = s->parent->curTransactionOwner;
	CurTransactionResourceOwner = s->parent->curTransactionOwner;
	if (s->curTransactionOwner)
		ResourceOwnerDelete(s->curTransactionOwner);
	s->curTransactionOwner = NULL;

	AtSubCleanup_Memory();

	s->state = TRANS_DEFAULT;

	PopTransaction();
}
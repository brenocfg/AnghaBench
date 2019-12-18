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
struct TYPE_5__ {scalar_t__ state; TYPE_1__* parent; int /*<<< orphan*/  subTransactionId; } ;
struct TYPE_4__ {int /*<<< orphan*/  subTransactionId; } ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerBeginSubXact () ; 
 int /*<<< orphan*/  AtSubStart_Memory () ; 
 int /*<<< orphan*/  AtSubStart_ResourceOwner () ; 
 int /*<<< orphan*/  CallSubXactCallbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* CurrentTransactionState ; 
 int /*<<< orphan*/  SUBXACT_EVENT_START_SUB ; 
 int /*<<< orphan*/  ShowTransactionState (char*) ; 
 scalar_t__ TRANS_DEFAULT ; 
 scalar_t__ TRANS_INPROGRESS ; 
 scalar_t__ TRANS_START ; 
 int /*<<< orphan*/  TransStateAsString (scalar_t__) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
StartSubTransaction(void)
{
	TransactionState s = CurrentTransactionState;

	if (s->state != TRANS_DEFAULT)
		elog(WARNING, "StartSubTransaction while in %s state",
			 TransStateAsString(s->state));

	s->state = TRANS_START;

	/*
	 * Initialize subsystems for new subtransaction
	 *
	 * must initialize resource-management stuff first
	 */
	AtSubStart_Memory();
	AtSubStart_ResourceOwner();
	AfterTriggerBeginSubXact();

	s->state = TRANS_INPROGRESS;

	/*
	 * Call start-of-subxact callbacks
	 */
	CallSubXactCallbacks(SUBXACT_EVENT_START_SUB, s->subTransactionId,
						 s->parent->subTransactionId);

	ShowTransactionState("StartSubTransaction");
}
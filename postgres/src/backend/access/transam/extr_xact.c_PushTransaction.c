#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionStateData ;
typedef  TYPE_1__* TransactionState ;
struct TYPE_4__ {scalar_t__ parallelModeLevel; int /*<<< orphan*/  prevXactReadOnly; int /*<<< orphan*/  prevSecContext; int /*<<< orphan*/  prevUser; int /*<<< orphan*/  blockState; int /*<<< orphan*/  state; int /*<<< orphan*/  savepointLevel; int /*<<< orphan*/  gucNestLevel; scalar_t__ nestingLevel; struct TYPE_4__* parent; scalar_t__ subTransactionId; int /*<<< orphan*/  fullTransactionId; } ;

/* Variables and functions */
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserIdAndSecContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidFullTransactionId ; 
 scalar_t__ InvalidSubTransactionId ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NewGUCNestLevel () ; 
 int /*<<< orphan*/  TBLOCK_SUBBEGIN ; 
 int /*<<< orphan*/  TRANS_DEFAULT ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 int /*<<< orphan*/  XactReadOnly ; 
 scalar_t__ currentSubTransactionId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
PushTransaction(void)
{
	TransactionState p = CurrentTransactionState;
	TransactionState s;

	/*
	 * We keep subtransaction state nodes in TopTransactionContext.
	 */
	s = (TransactionState)
		MemoryContextAllocZero(TopTransactionContext,
							   sizeof(TransactionStateData));

	/*
	 * Assign a subtransaction ID, watching out for counter wraparound.
	 */
	currentSubTransactionId += 1;
	if (currentSubTransactionId == InvalidSubTransactionId)
	{
		currentSubTransactionId -= 1;
		pfree(s);
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("cannot have more than 2^32-1 subtransactions in a transaction")));
	}

	/*
	 * We can now stack a minimally valid subtransaction without fear of
	 * failure.
	 */
	s->fullTransactionId = InvalidFullTransactionId;	/* until assigned */
	s->subTransactionId = currentSubTransactionId;
	s->parent = p;
	s->nestingLevel = p->nestingLevel + 1;
	s->gucNestLevel = NewGUCNestLevel();
	s->savepointLevel = p->savepointLevel;
	s->state = TRANS_DEFAULT;
	s->blockState = TBLOCK_SUBBEGIN;
	GetUserIdAndSecContext(&s->prevUser, &s->prevSecContext);
	s->prevXactReadOnly = XactReadOnly;
	s->parallelModeLevel = 0;

	CurrentTransactionState = s;

	/*
	 * AbortSubTransaction and CleanupSubTransaction have to be able to cope
	 * with the subtransaction from here on out; in particular they should not
	 * assume that it necessarily has a transaction context, resource owner,
	 * or XID.
	 */
}
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
struct TYPE_5__ {int blockState; TYPE_1__* parent; int /*<<< orphan*/  curTransactionOwner; int /*<<< orphan*/  subTransactionId; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  curTransactionOwner; int /*<<< orphan*/  subTransactionId; } ;

/* Variables and functions */
 int /*<<< orphan*/  AbortSubTransaction () ; 
 int /*<<< orphan*/  AbortTransaction () ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtAbort_Memory () ; 
 int /*<<< orphan*/  AtAbort_Portals () ; 
 int /*<<< orphan*/  AtCleanup_Memory () ; 
 int /*<<< orphan*/  AtSubAbort_Portals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CleanupSubTransaction () ; 
 int /*<<< orphan*/  CleanupTransaction () ; 
 TYPE_2__* CurrentTransactionState ; 
#define  TBLOCK_ABORT 147 
#define  TBLOCK_ABORT_END 146 
#define  TBLOCK_ABORT_PENDING 145 
#define  TBLOCK_BEGIN 144 
#define  TBLOCK_DEFAULT 143 
#define  TBLOCK_END 142 
#define  TBLOCK_IMPLICIT_INPROGRESS 141 
#define  TBLOCK_INPROGRESS 140 
#define  TBLOCK_PARALLEL_INPROGRESS 139 
#define  TBLOCK_PREPARE 138 
#define  TBLOCK_STARTED 137 
#define  TBLOCK_SUBABORT 136 
#define  TBLOCK_SUBABORT_END 135 
#define  TBLOCK_SUBABORT_PENDING 134 
#define  TBLOCK_SUBABORT_RESTART 133 
#define  TBLOCK_SUBBEGIN 132 
#define  TBLOCK_SUBCOMMIT 131 
#define  TBLOCK_SUBINPROGRESS 130 
#define  TBLOCK_SUBRELEASE 129 
#define  TBLOCK_SUBRESTART 128 
 int /*<<< orphan*/  TRANS_DEFAULT ; 
 int /*<<< orphan*/  TRANS_INPROGRESS ; 
 int /*<<< orphan*/  TRANS_START ; 

void
AbortOutOfAnyTransaction(void)
{
	TransactionState s = CurrentTransactionState;

	/* Ensure we're not running in a doomed memory context */
	AtAbort_Memory();

	/*
	 * Get out of any transaction or nested transaction
	 */
	do
	{
		switch (s->blockState)
		{
			case TBLOCK_DEFAULT:
				if (s->state == TRANS_DEFAULT)
				{
					/* Not in a transaction, do nothing */
				}
				else
				{
					/*
					 * We can get here after an error during transaction start
					 * (state will be TRANS_START).  Need to clean up the
					 * incompletely started transaction.  First, adjust the
					 * low-level state to suppress warning message from
					 * AbortTransaction.
					 */
					if (s->state == TRANS_START)
						s->state = TRANS_INPROGRESS;
					AbortTransaction();
					CleanupTransaction();
				}
				break;
			case TBLOCK_STARTED:
			case TBLOCK_BEGIN:
			case TBLOCK_INPROGRESS:
			case TBLOCK_IMPLICIT_INPROGRESS:
			case TBLOCK_PARALLEL_INPROGRESS:
			case TBLOCK_END:
			case TBLOCK_ABORT_PENDING:
			case TBLOCK_PREPARE:
				/* In a transaction, so clean up */
				AbortTransaction();
				CleanupTransaction();
				s->blockState = TBLOCK_DEFAULT;
				break;
			case TBLOCK_ABORT:
			case TBLOCK_ABORT_END:

				/*
				 * AbortTransaction is already done, still need Cleanup.
				 * However, if we failed partway through running ROLLBACK,
				 * there will be an active portal running that command, which
				 * we need to shut down before doing CleanupTransaction.
				 */
				AtAbort_Portals();
				CleanupTransaction();
				s->blockState = TBLOCK_DEFAULT;
				break;

				/*
				 * In a subtransaction, so clean it up and abort parent too
				 */
			case TBLOCK_SUBBEGIN:
			case TBLOCK_SUBINPROGRESS:
			case TBLOCK_SUBRELEASE:
			case TBLOCK_SUBCOMMIT:
			case TBLOCK_SUBABORT_PENDING:
			case TBLOCK_SUBRESTART:
				AbortSubTransaction();
				CleanupSubTransaction();
				s = CurrentTransactionState;	/* changed by pop */
				break;

			case TBLOCK_SUBABORT:
			case TBLOCK_SUBABORT_END:
			case TBLOCK_SUBABORT_RESTART:
				/* As above, but AbortSubTransaction already done */
				if (s->curTransactionOwner)
				{
					/* As in TBLOCK_ABORT, might have a live portal to zap */
					AtSubAbort_Portals(s->subTransactionId,
									   s->parent->subTransactionId,
									   s->curTransactionOwner,
									   s->parent->curTransactionOwner);
				}
				CleanupSubTransaction();
				s = CurrentTransactionState;	/* changed by pop */
				break;
		}
	} while (s->blockState != TBLOCK_DEFAULT);

	/* Should be out of all subxacts now */
	Assert(s->parent == NULL);

	/* If we didn't actually have anything to do, revert to TopMemoryContext */
	AtCleanup_Memory();
}
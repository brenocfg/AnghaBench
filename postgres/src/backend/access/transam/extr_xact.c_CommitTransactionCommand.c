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
struct TYPE_3__ {int chain; int blockState; char* name; int savepointLevel; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AbortSubTransaction () ; 
 int /*<<< orphan*/  AbortTransaction () ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertState (int) ; 
 int /*<<< orphan*/  BlockStateAsString (int) ; 
 int /*<<< orphan*/  CleanupSubTransaction () ; 
 int /*<<< orphan*/  CleanupTransaction () ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  CommitSubTransaction () ; 
 int /*<<< orphan*/  CommitTransaction () ; 
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  DefineSavepoint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  PrepareTransaction () ; 
 int /*<<< orphan*/  RestoreTransactionCharacteristics () ; 
 int /*<<< orphan*/  SaveTransactionCharacteristics () ; 
 int /*<<< orphan*/  StartSubTransaction () ; 
 int /*<<< orphan*/  StartTransaction () ; 
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
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
CommitTransactionCommand(void)
{
	TransactionState s = CurrentTransactionState;

	if (s->chain)
		SaveTransactionCharacteristics();

	switch (s->blockState)
	{
			/*
			 * These shouldn't happen.  TBLOCK_DEFAULT means the previous
			 * StartTransactionCommand didn't set the STARTED state
			 * appropriately, while TBLOCK_PARALLEL_INPROGRESS should be ended
			 * by EndParallelWorkerTransaction(), not this function.
			 */
		case TBLOCK_DEFAULT:
		case TBLOCK_PARALLEL_INPROGRESS:
			elog(FATAL, "CommitTransactionCommand: unexpected state %s",
				 BlockStateAsString(s->blockState));
			break;

			/*
			 * If we aren't in a transaction block, just do our usual
			 * transaction commit, and return to the idle state.
			 */
		case TBLOCK_STARTED:
			CommitTransaction();
			s->blockState = TBLOCK_DEFAULT;
			break;

			/*
			 * We are completing a "BEGIN TRANSACTION" command, so we change
			 * to the "transaction block in progress" state and return.  (We
			 * assume the BEGIN did nothing to the database, so we need no
			 * CommandCounterIncrement.)
			 */
		case TBLOCK_BEGIN:
			s->blockState = TBLOCK_INPROGRESS;
			break;

			/*
			 * This is the case when we have finished executing a command
			 * someplace within a transaction block.  We increment the command
			 * counter and return.
			 */
		case TBLOCK_INPROGRESS:
		case TBLOCK_IMPLICIT_INPROGRESS:
		case TBLOCK_SUBINPROGRESS:
			CommandCounterIncrement();
			break;

			/*
			 * We are completing a "COMMIT" command.  Do it and return to the
			 * idle state.
			 */
		case TBLOCK_END:
			CommitTransaction();
			s->blockState = TBLOCK_DEFAULT;
			if (s->chain)
			{
				StartTransaction();
				s->blockState = TBLOCK_INPROGRESS;
				s->chain = false;
				RestoreTransactionCharacteristics();
			}
			break;

			/*
			 * Here we are in the middle of a transaction block but one of the
			 * commands caused an abort so we do nothing but remain in the
			 * abort state.  Eventually we will get a ROLLBACK command.
			 */
		case TBLOCK_ABORT:
		case TBLOCK_SUBABORT:
			break;

			/*
			 * Here we were in an aborted transaction block and we just got
			 * the ROLLBACK command from the user, so clean up the
			 * already-aborted transaction and return to the idle state.
			 */
		case TBLOCK_ABORT_END:
			CleanupTransaction();
			s->blockState = TBLOCK_DEFAULT;
			if (s->chain)
			{
				StartTransaction();
				s->blockState = TBLOCK_INPROGRESS;
				s->chain = false;
				RestoreTransactionCharacteristics();
			}
			break;

			/*
			 * Here we were in a perfectly good transaction block but the user
			 * told us to ROLLBACK anyway.  We have to abort the transaction
			 * and then clean up.
			 */
		case TBLOCK_ABORT_PENDING:
			AbortTransaction();
			CleanupTransaction();
			s->blockState = TBLOCK_DEFAULT;
			if (s->chain)
			{
				StartTransaction();
				s->blockState = TBLOCK_INPROGRESS;
				s->chain = false;
				RestoreTransactionCharacteristics();
			}
			break;

			/*
			 * We are completing a "PREPARE TRANSACTION" command.  Do it and
			 * return to the idle state.
			 */
		case TBLOCK_PREPARE:
			PrepareTransaction();
			s->blockState = TBLOCK_DEFAULT;
			break;

			/*
			 * We were just issued a SAVEPOINT inside a transaction block.
			 * Start a subtransaction.  (DefineSavepoint already did
			 * PushTransaction, so as to have someplace to put the SUBBEGIN
			 * state.)
			 */
		case TBLOCK_SUBBEGIN:
			StartSubTransaction();
			s->blockState = TBLOCK_SUBINPROGRESS;
			break;

			/*
			 * We were issued a RELEASE command, so we end the current
			 * subtransaction and return to the parent transaction. The parent
			 * might be ended too, so repeat till we find an INPROGRESS
			 * transaction or subtransaction.
			 */
		case TBLOCK_SUBRELEASE:
			do
			{
				CommitSubTransaction();
				s = CurrentTransactionState;	/* changed by pop */
			} while (s->blockState == TBLOCK_SUBRELEASE);

			Assert(s->blockState == TBLOCK_INPROGRESS ||
				   s->blockState == TBLOCK_SUBINPROGRESS);
			break;

			/*
			 * We were issued a COMMIT, so we end the current subtransaction
			 * hierarchy and perform final commit. We do this by rolling up
			 * any subtransactions into their parent, which leads to O(N^2)
			 * operations with respect to resource owners - this isn't that
			 * bad until we approach a thousands of savepoints but is
			 * necessary for correctness should after triggers create new
			 * resource owners.
			 */
		case TBLOCK_SUBCOMMIT:
			do
			{
				CommitSubTransaction();
				s = CurrentTransactionState;	/* changed by pop */
			} while (s->blockState == TBLOCK_SUBCOMMIT);
			/* If we had a COMMIT command, finish off the main xact too */
			if (s->blockState == TBLOCK_END)
			{
				Assert(s->parent == NULL);
				CommitTransaction();
				s->blockState = TBLOCK_DEFAULT;
			}
			else if (s->blockState == TBLOCK_PREPARE)
			{
				Assert(s->parent == NULL);
				PrepareTransaction();
				s->blockState = TBLOCK_DEFAULT;
			}
			else
				elog(ERROR, "CommitTransactionCommand: unexpected state %s",
					 BlockStateAsString(s->blockState));
			break;

			/*
			 * The current already-failed subtransaction is ending due to a
			 * ROLLBACK or ROLLBACK TO command, so pop it and recursively
			 * examine the parent (which could be in any of several states).
			 */
		case TBLOCK_SUBABORT_END:
			CleanupSubTransaction();
			CommitTransactionCommand();
			break;

			/*
			 * As above, but it's not dead yet, so abort first.
			 */
		case TBLOCK_SUBABORT_PENDING:
			AbortSubTransaction();
			CleanupSubTransaction();
			CommitTransactionCommand();
			break;

			/*
			 * The current subtransaction is the target of a ROLLBACK TO
			 * command.  Abort and pop it, then start a new subtransaction
			 * with the same name.
			 */
		case TBLOCK_SUBRESTART:
			{
				char	   *name;
				int			savepointLevel;

				/* save name and keep Cleanup from freeing it */
				name = s->name;
				s->name = NULL;
				savepointLevel = s->savepointLevel;

				AbortSubTransaction();
				CleanupSubTransaction();

				DefineSavepoint(NULL);
				s = CurrentTransactionState;	/* changed by push */
				s->name = name;
				s->savepointLevel = savepointLevel;

				/* This is the same as TBLOCK_SUBBEGIN case */
				AssertState(s->blockState == TBLOCK_SUBBEGIN);
				StartSubTransaction();
				s->blockState = TBLOCK_SUBINPROGRESS;
			}
			break;

			/*
			 * Same as above, but the subtransaction had already failed, so we
			 * don't need AbortSubTransaction.
			 */
		case TBLOCK_SUBABORT_RESTART:
			{
				char	   *name;
				int			savepointLevel;

				/* save name and keep Cleanup from freeing it */
				name = s->name;
				s->name = NULL;
				savepointLevel = s->savepointLevel;

				CleanupSubTransaction();

				DefineSavepoint(NULL);
				s = CurrentTransactionState;	/* changed by push */
				s->name = name;
				s->savepointLevel = savepointLevel;

				/* This is the same as TBLOCK_SUBBEGIN case */
				AssertState(s->blockState == TBLOCK_SUBBEGIN);
				StartSubTransaction();
				s->blockState = TBLOCK_SUBINPROGRESS;
			}
			break;
	}
}
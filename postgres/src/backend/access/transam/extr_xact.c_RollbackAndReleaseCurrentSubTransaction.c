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
struct TYPE_3__ {int blockState; } ;

/* Variables and functions */
 int /*<<< orphan*/  AbortSubTransaction () ; 
 int /*<<< orphan*/  AssertState (int) ; 
 int /*<<< orphan*/  BlockStateAsString (int) ; 
 int /*<<< orphan*/  CleanupSubTransaction () ; 
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  FATAL ; 
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
RollbackAndReleaseCurrentSubTransaction(void)
{
	TransactionState s = CurrentTransactionState;

	/*
	 * Unlike ReleaseCurrentSubTransaction(), this is nominally permitted
	 * during parallel operations.  That's because we may be in the master,
	 * recovering from an error thrown while we were in parallel mode.  We
	 * won't reach here in a worker, because BeginInternalSubTransaction()
	 * will have failed.
	 */

	switch (s->blockState)
	{
			/* Must be in a subtransaction */
		case TBLOCK_SUBINPROGRESS:
		case TBLOCK_SUBABORT:
			break;

			/* These cases are invalid. */
		case TBLOCK_DEFAULT:
		case TBLOCK_STARTED:
		case TBLOCK_BEGIN:
		case TBLOCK_IMPLICIT_INPROGRESS:
		case TBLOCK_PARALLEL_INPROGRESS:
		case TBLOCK_SUBBEGIN:
		case TBLOCK_INPROGRESS:
		case TBLOCK_END:
		case TBLOCK_SUBRELEASE:
		case TBLOCK_SUBCOMMIT:
		case TBLOCK_ABORT:
		case TBLOCK_ABORT_END:
		case TBLOCK_SUBABORT_END:
		case TBLOCK_ABORT_PENDING:
		case TBLOCK_SUBABORT_PENDING:
		case TBLOCK_SUBRESTART:
		case TBLOCK_SUBABORT_RESTART:
		case TBLOCK_PREPARE:
			elog(FATAL, "RollbackAndReleaseCurrentSubTransaction: unexpected state %s",
				 BlockStateAsString(s->blockState));
			break;
	}

	/*
	 * Abort the current subtransaction, if needed.
	 */
	if (s->blockState == TBLOCK_SUBINPROGRESS)
		AbortSubTransaction();

	/* And clean it up, too */
	CleanupSubTransaction();

	s = CurrentTransactionState;	/* changed by pop */
	AssertState(s->blockState == TBLOCK_SUBINPROGRESS ||
				s->blockState == TBLOCK_INPROGRESS ||
				s->blockState == TBLOCK_IMPLICIT_INPROGRESS ||
				s->blockState == TBLOCK_STARTED);
}
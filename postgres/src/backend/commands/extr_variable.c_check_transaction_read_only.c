#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_ACTIVE_SQL_TRANSACTION ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 scalar_t__ FirstSnapshotSet ; 
 int /*<<< orphan*/  GUC_check_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_check_errmsg (char*) ; 
 int /*<<< orphan*/  InitializingParallelWorker ; 
 scalar_t__ IsSubTransaction () ; 
 scalar_t__ IsTransactionState () ; 
 scalar_t__ RecoveryInProgress () ; 
 scalar_t__ XactReadOnly ; 

bool
check_transaction_read_only(bool *newval, void **extra, GucSource source)
{
	if (*newval == false && XactReadOnly && IsTransactionState() && !InitializingParallelWorker)
	{
		/* Can't go to r/w mode inside a r/o transaction */
		if (IsSubTransaction())
		{
			GUC_check_errcode(ERRCODE_ACTIVE_SQL_TRANSACTION);
			GUC_check_errmsg("cannot set transaction read-write mode inside a read-only transaction");
			return false;
		}
		/* Top level transaction can't change to r/w after first snapshot. */
		if (FirstSnapshotSet)
		{
			GUC_check_errcode(ERRCODE_ACTIVE_SQL_TRANSACTION);
			GUC_check_errmsg("transaction read-write mode must be set before any query");
			return false;
		}
		/* Can't go to r/w mode while recovery is still active */
		if (RecoveryInProgress())
		{
			GUC_check_errcode(ERRCODE_FEATURE_NOT_SUPPORTED);
			GUC_check_errmsg("cannot set transaction read-write mode during recovery");
			return false;
		}
	}

	return true;
}
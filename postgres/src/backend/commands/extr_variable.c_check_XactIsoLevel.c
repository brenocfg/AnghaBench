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
 int /*<<< orphan*/  GUC_check_errhint (char*) ; 
 int /*<<< orphan*/  GUC_check_errmsg (char*) ; 
 scalar_t__ IsSubTransaction () ; 
 scalar_t__ IsTransactionState () ; 
 scalar_t__ RecoveryInProgress () ; 
 int XACT_SERIALIZABLE ; 
 int XactIsoLevel ; 

bool
check_XactIsoLevel(int *newval, void **extra, GucSource source)
{
	int			newXactIsoLevel = *newval;

	if (newXactIsoLevel != XactIsoLevel && IsTransactionState())
	{
		if (FirstSnapshotSet)
		{
			GUC_check_errcode(ERRCODE_ACTIVE_SQL_TRANSACTION);
			GUC_check_errmsg("SET TRANSACTION ISOLATION LEVEL must be called before any query");
			return false;
		}
		/* We ignore a subtransaction setting it to the existing value. */
		if (IsSubTransaction())
		{
			GUC_check_errcode(ERRCODE_ACTIVE_SQL_TRANSACTION);
			GUC_check_errmsg("SET TRANSACTION ISOLATION LEVEL must not be called in a subtransaction");
			return false;
		}
		/* Can't go to serializable mode while recovery is still active */
		if (newXactIsoLevel == XACT_SERIALIZABLE && RecoveryInProgress())
		{
			GUC_check_errcode(ERRCODE_FEATURE_NOT_SUPPORTED);
			GUC_check_errmsg("cannot use serializable mode in a hot standby");
			GUC_check_errhint("You can use REPEATABLE READ instead.");
			return false;
		}
	}

	return true;
}
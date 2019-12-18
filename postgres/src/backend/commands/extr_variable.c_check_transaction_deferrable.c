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
 scalar_t__ FirstSnapshotSet ; 
 int /*<<< orphan*/  GUC_check_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_check_errmsg (char*) ; 
 scalar_t__ IsSubTransaction () ; 

bool
check_transaction_deferrable(bool *newval, void **extra, GucSource source)
{
	if (IsSubTransaction())
	{
		GUC_check_errcode(ERRCODE_ACTIVE_SQL_TRANSACTION);
		GUC_check_errmsg("SET TRANSACTION [NOT] DEFERRABLE cannot be called within a subtransaction");
		return false;
	}
	if (FirstSnapshotSet)
	{
		GUC_check_errcode(ERRCODE_ACTIVE_SQL_TRANSACTION);
		GUC_check_errmsg("SET TRANSACTION [NOT] DEFERRABLE must be called before any query");
		return false;
	}

	return true;
}
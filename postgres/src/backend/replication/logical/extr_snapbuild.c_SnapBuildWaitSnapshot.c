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
struct TYPE_3__ {int xcnt; int /*<<< orphan*/ * xids; } ;
typedef  TYPE_1__ xl_running_xacts ;
typedef  int /*<<< orphan*/  TransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LogStandbySnapshot () ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 scalar_t__ TransactionIdFollows (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLTW_None ; 
 int /*<<< orphan*/  XactLockTableWait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
SnapBuildWaitSnapshot(xl_running_xacts *running, TransactionId cutoff)
{
	int			off;

	for (off = 0; off < running->xcnt; off++)
	{
		TransactionId xid = running->xids[off];

		/*
		 * Upper layers should prevent that we ever need to wait on ourselves.
		 * Check anyway, since failing to do so would either result in an
		 * endless wait or an Assert() failure.
		 */
		if (TransactionIdIsCurrentTransactionId(xid))
			elog(ERROR, "waiting for ourselves");

		if (TransactionIdFollows(xid, cutoff))
			continue;

		XactLockTableWait(xid, NULL, NULL, XLTW_None);
	}

	/*
	 * All transactions we needed to finish finished - try to ensure there is
	 * another xl_running_xacts record in a timely manner, without having to
	 * write for bgwriter or checkpointer to log one.  During recovery we
	 * can't enforce that, so we'll have to wait.
	 */
	if (!RecoveryInProgress())
	{
		LogStandbySnapshot();
	}
}
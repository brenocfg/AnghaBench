#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_6__ {scalar_t__ Flush; } ;
struct TYPE_5__ {scalar_t__ walwriterLatch; } ;
struct TYPE_4__ {int WalWriterSleeping; scalar_t__ asyncXactLSN; int /*<<< orphan*/  info_lck; TYPE_3__ LogwrtResult; } ;

/* Variables and functions */
 TYPE_3__ LogwrtResult ; 
 TYPE_2__* ProcGlobal ; 
 int /*<<< orphan*/  SetLatch (scalar_t__) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ XLOG_BLCKSZ ; 
 TYPE_1__* XLogCtl ; 

void
XLogSetAsyncXactLSN(XLogRecPtr asyncXactLSN)
{
	XLogRecPtr	WriteRqstPtr = asyncXactLSN;
	bool		sleeping;

	SpinLockAcquire(&XLogCtl->info_lck);
	LogwrtResult = XLogCtl->LogwrtResult;
	sleeping = XLogCtl->WalWriterSleeping;
	if (XLogCtl->asyncXactLSN < asyncXactLSN)
		XLogCtl->asyncXactLSN = asyncXactLSN;
	SpinLockRelease(&XLogCtl->info_lck);

	/*
	 * If the WALWriter is sleeping, we should kick it to make it come out of
	 * low-power mode.  Otherwise, determine whether there's a full page of
	 * WAL available to write.
	 */
	if (!sleeping)
	{
		/* back off to last completed page boundary */
		WriteRqstPtr -= WriteRqstPtr % XLOG_BLCKSZ;

		/* if we have already flushed that far, we're done */
		if (WriteRqstPtr <= LogwrtResult.Flush)
			return;
	}

	/*
	 * Nudge the WALWriter: it has a full page of WAL to write, or we want it
	 * to come out of low-power mode so that this async commit will reach disk
	 * within the expected amount of time.
	 */
	if (ProcGlobal->walwriterLatch)
		SetLatch(ProcGlobal->walwriterLatch);
}